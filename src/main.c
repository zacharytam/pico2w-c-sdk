#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    
    // Initialize LED
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Firmware starting...\n");
    
    int counter = 0;
    while (true) {
        gpio_put(LED_PIN, 1);
        printf("LED ON - Count: %d\n", counter);
        sleep_ms(500);
        
        gpio_put(LED_PIN, 0);
        printf("LED OFF - Count: %d\n", counter);
        sleep_ms(500);
        
        counter++;
    }
    
    return 0;
}
