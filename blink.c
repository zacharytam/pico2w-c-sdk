#include "pico/stdlib.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

int main() {
    // Initialize the onboard LED pin
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);

    // Blink loop
    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, true);  // LED ON
        sleep_ms(LED_DELAY_MS);
        gpio_put(PICO_DEFAULT_LED_PIN, false); // LED OFF
        sleep_ms(LED_DELAY_MS);
    }

    return 0;
}
