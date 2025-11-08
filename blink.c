#include "pico/stdlib.h"
#include "pico/cyw43_arch.h" // For Pico 2 W Wi-Fi/LED GPIO

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

int main() {
    int rc = cyw43_arch_init();
    if (rc != 0) return rc; // Fail if Wi-Fi driver/LED init fails

    // Blink LED in a loop
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        sleep_ms(LED_DELAY_MS);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
        sleep_ms(LED_DELAY_MS);
    }

    return 0;
}
