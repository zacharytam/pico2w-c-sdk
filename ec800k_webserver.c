#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/stdio_usb.h"
#include "hardware/uart.h"
#include <string.h>
#include <stdio.h>

// =========================
// Configuration
// =========================
#define UART_ID uart0
#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define UART_BAUDRATE 230400

#define WIFI_SSID "Pico2W-EC800K"
#define WIFI_PASS "pico12345"

#define SERVER_PORT 80
#define BUF_SIZE 2048

// =========================
// Simple HTTP Response Page
// =========================
static const char html_page[] =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n\r\n"
    "<!DOCTYPE html><html><head><meta charset='utf-8'>"
    "<title>Pico2W EC800K Control</title>"
    "<style>body{font-family:sans-serif;margin:2em;}button{margin:5px;padding:10px;}</style>"
    "</head><body>"
    "<h2>Pico2W → EC800K</h2>"
    "<form action='/send' method='get'>"
    "<button name='cmd' value='AT'>AT</button>"
    "<button name='cmd' value='ATI'>ATI</button>"
    "<button name='cmd' value='AT+CSQ'>Signal</button><br>"
    "Custom: <input name='cmd' type='text' placeholder='AT+...'>"
    "<input type='submit' value='Send'>"
    "</form>"
    "<hr><pre>Response:\r\n"
    "{RESP}</pre></body></html>";

// =========================
// UART helpers
// =========================
void uart_init_ec800k(void) {
    uart_init(UART_ID, UART_BAUDRATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    printf("UART initialized at %d baud.\n", UART_BAUDRATE);
}

void uart_send_command(const char *cmd) {
    uart_puts(UART_ID, cmd);
    uart_puts(UART_ID, "\r\n"); // append CRLF
    printf("UART TX: %s\n", cmd);
}

int uart_read_response(char *buf, int maxlen, uint timeout_ms) {
    int idx = 0;
    absolute_time_t end = make_timeout_time_ms(timeout_ms);
    while (absolute_time_diff_us(get_absolute_time(), end) > 0 && idx < maxlen - 1) {
        if (uart_is_readable(UART_ID)) {
            char c = uart_getc(UART_ID);
            buf[idx++] = c;
        }
    }
    buf[idx] = 0;
    return idx;
}

// =========================
// HTTP server helpers
// =========================
bool parse_cmd_param(const char *req, char *cmd_out, size_t maxlen) {
    const char *p = strstr(req, "cmd=");
    if (!p) return false;
    p += 4;
    int i = 0;
    while (*p && *p != ' ' && *p != '&' && i < maxlen - 1) {
        cmd_out[i++] = *p++;
    }
    cmd_out[i] = '\0';
    return i > 0;
}

// Replace {RESP} placeholder with actual UART reply
void make_response(char *out_buf, const char *reply) {
    const char *placeholder = strstr(html_page, "{RESP}");
    if (!placeholder) {
        snprintf(out_buf, BUF_SIZE, "%s", html_page);
        return;
    }
    int prefix_len = placeholder - html_page;
    strncpy(out_buf, html_page, prefix_len);
    out_buf[prefix_len] = '\0';
    strcat(out_buf, reply);
    strcat(out_buf, placeholder + 6);
}

// =========================
// Main program
// =========================
int main() {
    stdio_init_all();
    sleep_ms(1000);
    printf("=== Pico2W EC800K Webserver ===\n");

    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed!\n");
        return -1;
    }

    // Start Access Point
    printf("Starting AP: %s\n", WIFI_SSID);
    cyw43_arch_enable_ap_mode(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK);
    printf("AP started, waiting for clients...\n");

    // Setup UART
    uart_init_ec800k();

    // Setup TCP server
    int server_sock = lwip_socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        printf("Socket create failed!\n");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_len = sizeof(addr);
    addr.sin_family = AF_INET;
    addr.sin_port = PP_HTONS(SERVER_PORT);
    addr.sin_addr.s_addr = PP_HTONL(INADDR_ANY);

    if (lwip_bind(server_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("Bind failed!\n");
        return -1;
    }

    lwip_listen(server_sock, 1);
    printf("HTTP server listening on 192.168.4.1:%d\n", SERVER_PORT);

    char req_buf[BUF_SIZE];
    char resp_buf[BUF_SIZE];
    char uart_reply[512];
    char cmd[128];

    while (true) {
        struct sockaddr_in client;
        socklen_t clen = sizeof(client);
        int client_sock = lwip_accept(server_sock, (struct sockaddr *)&client, &clen);
        if (client_sock < 0) continue;

        int len = lwip_recv(client_sock, req_buf, sizeof(req_buf) - 1, 0);
        if (len <= 0) {
            lwip_close(client_sock);
            continue;
        }

        req_buf[len] = '\0';
        printf("HTTP Request:\n%s\n", req_buf);

        if (parse_cmd_param(req_buf, cmd, sizeof(cmd))) {
            uart_send_command(cmd);
            int n = uart_read_response(uart_reply, sizeof(uart_reply), 500);
            if (n == 0) strcpy(uart_reply, "<no response>");
        } else {
            strcpy(uart_reply, "(no command)");
        }

        make_response(resp_buf, uart_reply);
        lwip_send(client_sock, resp_buf, strlen(resp_buf), 0);
        lwip_close(client_sock);
    }

    cyw43_arch_deinit();
    return 0;
}
