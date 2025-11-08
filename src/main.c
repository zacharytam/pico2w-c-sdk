#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

// Binary info metadata
bi_decl(bi_program_name("pico2w_lte_router"));
bi_decl(bi_program_description("LTE Router firmware for Raspberry Pi Pico 2W"));
bi_decl(bi_program_version_string("1.0"));

// LED configuration
const uint LED_PIN = 25;
bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

int main() {
    // Initialize stdio immediately
    stdio_init_all();
    
    // Initialize LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Wait a bit for serial
    sleep_ms(2500);
    
    printf("\n\n=== Pico 2W LTE Router ===\n");
    printf("LED on GPIO %d\n", LED_PIN);
    printf("Firmware starting...\n");
    
    // Distinctive startup pattern: 3 quick blinks
    for (int i = 0; i < 3; i++) {
        gpio_put(LED_PIN, 1);
        sleep_ms(150);
        gpio_put(LED_PIN, 0);
        sleep_ms(150);
    }
    
    printf("Startup complete. Entering main loop.\n");
    
    int counter = 0;
    while (true) {
        // Blink with serial output
        gpio_put(LED_PIN, 1);
        printf("Count: %d - LED ON\n", counter);
        sleep_ms(300);
        
        gpio_put(LED_PIN, 0);
        printf("Count: %d - LED OFF\n", counter);
        sleep_ms(700);
        
        counter++;
    }
    
    return 0;
}
