#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

// Add binary info metadata - CRITICAL for auto-reboot
bi_decl(bi_program_name("Pico 2W LTE Router"));
bi_decl(bi_program_description("LTE Router firmware for Raspberry Pi Pico 2W"));
bi_decl(bi_program_version_string("1.0.0"));

// Define the LED pin with binary info
const uint LED_PIN = 25;
bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

int main() {
    stdio_init_all();
    
    // Wait for serial connection
    sleep_ms(1000);
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Firmware starting...\n");
    
    // Initialize LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Fast blink at startup to indicate successful boot
    for (int i = 0; i < 5; i++) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    }
    
    printf("Startup complete. Beginning main loop...\n");
    
    int counter = 0;
    while (true) {
        gpio_put(LED_PIN, 1);
        printf("Count: %d - LED ON\n", counter);
        sleep_ms(500);
        
        gpio_put(LED_PIN, 0);
        printf("Count: %d - LED OFF\n", counter);
        sleep_ms(500);
        
        counter++;
    }
    
    return 0;
}
