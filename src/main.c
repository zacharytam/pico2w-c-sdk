/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

// Perform initialisation
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Pico with GPIO LED
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Pico W - initialise the wifi driver
    return cyw43_arch_init();
#else
    return PICO_ERROR_NOT_PERMITTED;
#endif
}

// Turn the led on or off
void pico_set_led(bool led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

int main() {
    stdio_init_all();
    sleep_ms(2000); // Wait for serial
    
    printf("=== Pico 2W LTE Router ===\n");
    printf("Firmware starting...\n");
    
    int rc = pico_led_init();
    if (rc != PICO_OK) {
        printf("LED init failed: %d\n", rc);
        return rc;
    }
    
    printf("LED initialized successfully\n");
    printf("Starting blink pattern...\n");
    
    int counter = 0;
    while (true) {
        pico_set_led(true);
        printf("Count: %d - LED ON\n", counter);
        sleep_ms(500);
        pico_set_led(false);
        printf("Count: %d - LED OFF\n", counter);
        sleep_ms(500);
        counter++;
    }
    
    return 0;
}

