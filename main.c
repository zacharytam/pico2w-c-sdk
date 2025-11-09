#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/uart.h"
#include "lwip/apps/httpd.h"
#include "lwip/tcpip.h"
#include <string.h>

#define UART_ID uart1
#define UART_TX_PIN 4
#define UART_RX_PIN 5
#define BAUD_RATE 115200

// Simple HTML page
static const char *webpage =
"<!DOCTYPE html>"
"<html><head><title>Pico 2W HTTP</title></head>"
"<body><h1>Pico 2 W + EC800K</h1>"
"<p>Status: Connected</p>"
"</body></html>";

// Custom HTTP handler
static const char* http_server_index_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    (void)iIndex; (void)iNumParams; (void)pcParam; (void)pcValue;
    return webpage;
}

void http_server_init_custom(void) {
    httpd_init();
    http_set_ssi_handler(http_server_index_handler, NULL, 0);
}

int main() {
    stdio_init_all();

    printf("Starting Pico 2 W AP + HTTP server + UART\n");

    // Init CYW43 (Wi-Fi + LED)
    if (cyw43_arch_init()) {
        printf("CYW43 init failed!\n");
        return -1;
    }

    // Start Wi-Fi AP mode
    cyw43_arch_enable_ap_mode("Pico2W-EC800K", "12345678", CYW43_AUTH_WPA2_AES_PSK);
    printf("Access Point started: SSID 'Pico2W-EC800K', IP 192.168.4.1\n");

    // Init UART for EC800K
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
    printf("UART initialized for EC800K at %d baud\n", BAUD_RATE);

    // Init TCP/IP stack and HTTP server
    tcpip_init(NULL, NULL);
    http_server_init_custom();

    // Blink LED to show server active
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);

        // Example UART loopback print
        uart_puts(UART_ID, "AT\r\n");
    }

    cyw43_arch_deinit();
    return 0;
}
