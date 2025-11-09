#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

#include "lwip/apps/httpd.h"
#include "lwip/apps/mdns.h"
#include "lwip/init.h"

static bool led_on = false;
static absolute_time_t wifi_connected_time;

static const char *cgi_handler_led(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]) {
    if (iNumParams > 0 && strcmp(pcParam[0], "led") == 0) {
        led_on = (strcmp(pcValue[0], "ON") == 0);
        cyw43_gpio_set(&cyw43_state, 0, led_on); // GPIO 0 on Wi-Fi chip
    }
    return "/index.shtml";
}

static tCGI cgi_handlers[] = {
    { "/", cgi_handler_led },
    { "/index.shtml", cgi_handler_led },
};

static const char *ssi_tags[] = { "ledstate", "uptime" };

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {
    switch (iIndex) {
        case 0: // ledstate
            return snprintf(pcInsert, iInsertLen, "%s", led_on ? "ON" : "OFF");
        case 1: // uptime
            return snprintf(pcInsert, iInsertLen, "%llu", 
                absolute_time_diff_us(wifi_connected_time, get_absolute_time()) / 1000000);
    }
    return 0;
}

int main() {
    stdio_init_all();

    if (cyw43_arch_init()) {
        printf("Failed to init cyw43_arch\n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    printf("Connecting to Wi-Fi...\n");
    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Failed to connect.\n");
        return 1;
    }
    printf("Connected.\n");

    wifi_connected_time = get_absolute_time();

#if LWIP_MDNS_RESPONDER
    cyw43_arch_lwip_begin();
    mdns_resp_init();
    mdns_resp_add_netif(&cyw43_state.netif[CYW43_ITF_STA], "pico_httpd");
    cyw43_arch_lwip_end();
#endif

    cyw43_arch_lwip_begin();
    httpd_init();
    http_set_cgi_handlers(cgi_handlers, LWIP_ARRAYSIZE(cgi_handlers));
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
    cyw43_arch_lwip_end();

    while (true) {
        sleep_ms(1000);
    }

    cyw43_arch_deinit();
}
