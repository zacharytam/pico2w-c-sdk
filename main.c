#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/lwip/tcpip.h"
#include "pico/lwip/apps/httpd.h"
#include "pico/lwip/apps/mdns.h"
#include "lwipopts.h"

#define LED_PIN 25

// SSI handler: updated signature for SDK 2.1.0
u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen,
                  u16_t current_tag_part, u16_t *next_tag_part) {
    // Example: insert LED status
    if (iIndex == 0) {
        pcInsert[0] = gpio_get(LED_PIN) ? '1' : '0';
        return 1; // length of data inserted
    }
    return 0;
}

const char *ssi_tags[] = {"led_status"};

int main() {
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Initialize Wi-Fi
    if (cyw43_arch_init()) {
        printf("Wi-Fi init failed\n");
        return -1;
    }

    // Add MDNS for Pico HTTPD (updated: only 2 args)
    mdns_resp_add_netif(&cyw43_state.netif[CYW43_ITF_STA], "pico_httpd");

    // Setup HTTP server
    httpd_init();
    http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));

    while (true) {
        // Example: toggle LED
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
}
