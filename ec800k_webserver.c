#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"  // Wi-Fi + LED

#define LED_DELAY_MS 250

int main() {
    // Initialize Wi-Fi driver (needed to control onboard LED)
    if (cyw43_arch_init()) {
        return -1;  // Initialization failed
    }

    while (true) {
        // Turn LED on
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true);
        sleep_ms(LED_DELAY_MS);

        // Turn LED off
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false);
        sleep_ms(LED_DELAY_MS);
    }

    cyw43_arch_deinit();
    return 0;
}
