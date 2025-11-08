#include "pico/stdlib.h"

#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

int main() {
    int rc = 0;

#if defined(PICO_DEFAULT_LED_PIN)
    // Initialize GPIO for LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Initialize Wi-Fi driver for Pico 2 W
    rc = cyw43_arch_init();
    if (rc != 0) return rc;
#endif

    // Blink loop
    while (true) {
#if defined(PICO_DEFAULT_LED_PIN)
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(LED_DELAY_MS);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(LED_DELAY_MS);
#elif defined(CYW43_WL_GPIO_LED_PIN)
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        sleep_ms(LED_DELAY_MS);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
        sleep_ms(LED_DELAY_MS);
#endif
    }

    return 0;
}
