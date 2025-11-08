#include "pico/stdlib.h"
#include "pico/binary_info.h"

// CRITICAL: Add binary info for auto-reboot
bi_decl(bi_program_name("simple_blink"));
bi_decl(bi_program_description("Simple blink test for Pico 2W"));
bi_decl(bi_program_version_string("1.0"));

const uint LED_PIN = 25;

// Add binary info for the LED pin
bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}
