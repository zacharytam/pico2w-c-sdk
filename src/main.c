#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

// Complete binary info
bi_decl(bi_program_name("pico2w_lte_router"));
bi_decl(bi_program_description("LTE Router firmware for Raspberry Pi Pico 2W"));
bi_decl(bi_program_version_string("1.0"));

// LED configuration
const uint LED_PIN = 25;
bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

int main() {
    // Initialize immediately
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Very short delay
    sleep_ms(100);
    
    // Fast startup blink
    for (int i = 0; i < 6; i++) {
        gpio_put(LED_PIN, 1);
        sleep_ms(50);
        gpio_put(LED_PIN, 0);
        sleep_ms(50);
    }
    
    printf("=== Pico 2W LTE Router ===\n");
    
    // Main loop
    int counter = 0;
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(700);
        
        printf("Count: %d\n", counter++);
    }
    
    return 0;
}
