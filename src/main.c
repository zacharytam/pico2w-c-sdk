#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    
    // Pico 2W LED is on GPIO 25 (same as Pico W)
    // But we need to define it manually since PICO_DEFAULT_LED_PIN might not be defined
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Firmware starting...\n");
    printf("LED on GPIO %d\n", LED_PIN);
    
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
