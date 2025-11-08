#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
    // Initialize stdio
    stdio_init_all();
    
    // Wait a bit for serial connection
    sleep_ms(2000);
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Initializing...\n");
    
    // Initialize CYW43 driver (required for Pico W LED)
    if (cyw43_arch_init()) {
        printf("ERROR: CYW43 init failed!\n");
        return -1;
    }
    
    printf("CYW43 initialized successfully\n");
    printf("LED should start blinking...\n");
    
    int counter = 0;
    while (true) {
        // Turn LED ON
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        printf("Count: %d - LED ON\n", counter);
        sleep_ms(500);
        
        // Turn LED OFF
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        printf("Count: %d - LED OFF\n", counter);
        sleep_ms(500);
        
        counter++;
        
        // Reset counter periodically
        if (counter > 1000) {
            counter = 0;
        }
    }
    
    // Cleanup (we never get here)
    cyw43_arch_deinit();
    return 0;
}

