#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

// Add binary info metadata - THIS IS CRITICAL FOR AUTO-REBOOT
bi_decl(bi_program_name("Pico 2W LTE Router"));
bi_decl(bi_program_description("LTE Router firmware for Raspberry Pi Pico 2W"));
bi_decl(bi_program_version_string("1.0.0"));
bi_decl(bi_program_url("https://github.com/zacharytam/pico2w-c-sdk"));

// Define the LED pin with binary info
const uint LED_PIN = 25;
bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

int main() {
    stdio_init_all();
    
    // Wait a bit for serial connection
    sleep_ms(1000);
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Firmware starting...\n");
    printf("LED on GPIO %d\n", LED_PIN);
    
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
        printf("LED ON - Count: %d\n", counter);
        sleep_ms(500);
        
        gpio_put(LED_PIN, 0);
        printf("LED OFF - Count: %d\n", counter);
        sleep_ms(500);
        
        counter++;
        
        if (counter > 1000) counter = 0;
    }
    
    return 0;
}

