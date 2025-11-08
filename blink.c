#include "pico/stdlib.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

int main() {
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, true);

    while (true) {
        gpio_put(PICO_DEFAULT_LED_PIN, true);
        sleep_ms(LED_DELAY_MS);
        gpio_put(PICO_DEFAULT_LED_PIN, false);
        sleep_ms(LED_DELAY_MS);
    }

    return 0;
}
