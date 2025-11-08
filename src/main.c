#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"

// COMPLETE binary info - CRITICAL for auto-reboot
bi_decl(bi_program_name("pico2w_lte_router"));
bi_decl(bi_program_description("LTE Router firmware for Raspberry Pi Pico 2W"));
bi_decl(bi_program_version_string("1.0"));
bi_decl(bi_program_build_date_string(__DATE__));

// Define the LED pin with proper binary info
#define LED_PIN 25
bi_decl(bi_1pin_with_name(LED_PIN, "On-board LED"));

// Add program features section
bi_decl(bi_block_device(
    BINARY_INFO_MAKE_TAG('P', 'I'),
    "PicoApp",
    NULL,
    0x10000000,
    0x10000000
));

// Force a specific entry point structure
void __attribute__((naked)) _reset_handler(void) {
    // Minimal reset handler
    asm volatile (
        "ldr r0, =_stack_top\n"
        "mov sp, r0\n"
        "bl main\n"
        "b .\n"
    );
}

int main() {
    // Initialize immediately
    stdio_init_all();
    
    // Initialize LED immediately
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    // Very short delay only
    sleep_ms(100);
    
    // Immediate LED activity - fast blink pattern
    for (int i = 0; i < 8; i++) {
        gpio_put(LED_PIN, 1);
        sleep_ms(80);
        gpio_put(LED_PIN, 0);
        sleep_ms(80);
    }
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Firmware running - auto-reboot test\n");
    
    // Main loop with distinctive pattern
    int counter = 0;
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(200);
        gpio_put(LED_PIN, 0);
        sleep_ms(200);
        gpio_put(LED_PIN, 1);
        sleep_ms(200);
        gpio_put(LED_PIN, 0);
        sleep_ms(400);
        
        printf("Running: %d\n", counter++);
    }
    
    return 0;
}
