#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    sleep_ms(2000);  // Wait for serial
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Build successful! 🎉\n");
    printf("Board: Pico W/2W\n");
    printf("Basic firmware working\n");
    
    // Blink LED if available (GP25 on Pico W)
    #ifdef PICO_DEFAULT_LED_PIN
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    #endif
    
    int counter = 0;
    while (true) {
        printf("Counter: %d\n", counter++);
        
        #ifdef PICO_DEFAULT_LED_PIN
        gpio_put(PICO_DEFAULT_LED_PIN, counter % 2);
        #endif
        
        sleep_ms(1000);
    }
    
    return 0;
}

