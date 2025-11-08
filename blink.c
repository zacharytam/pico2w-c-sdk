#include "pico/stdlib.h"

#ifndef LED_PIN
#define LED_PIN 25   // Pico 2 W onboard LED
#endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, true);

    while (true) {
        gpio_put(LED_PIN, true);  // LED ON
        sleep_ms(LED_DELAY_MS);
        gpio_put(LED_PIN, false); // LED OFF
        sleep_ms(LED_DELAY_MS);
    }

    return 0;
}
