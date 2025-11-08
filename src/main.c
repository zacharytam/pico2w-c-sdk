#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    sleep_ms(2000);  // Wait for serial
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Build successful! 🎉\n");
    printf("Board: Pico W/2W\n");
    
    while (true) {
        printf("Running...\n");
        sleep_ms(5000);
    }
    
    return 0;
}
