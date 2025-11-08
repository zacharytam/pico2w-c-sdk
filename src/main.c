#include <stdio.h>
#include "pico/stdlib.h"

int main() {
    stdio_init_all();
    printf("Pico 2W LTE Router Starting...\n");
    
    while (true) {
        printf("Hello from Pico 2W!\n");
        sleep_ms(1000);
    }
    
    return 0;
}
