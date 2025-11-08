#include "pico/stdlib.h"
#include "pico/binary_info.h"

// Mark the LED pin in binary info (helps with UF2)
bi_decl(bi_program_description("Pico 2W LTE Router"))
bi_decl(bi_1pin_with_name(PICO_DEFAULT_LED_PIN, "On-board LED"))

int main() {
    // Initialize LED
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Simple blink pattern
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(700);
    }
    
    return 0;
}
