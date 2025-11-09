cmake_minimum_required(VERSION 3.13)

# Import Pico SDK
include(pico_sdk_import.cmake)

project(pico2w_ap_http C CXX ASM)

pico_sdk_init()

# Add executable
add_executable(pico2w_ap_http
    main.c
)

# Enable stdio over USB for debug (optional)
pico_enable_stdio_usb(pico2w_ap_http 1)
pico_enable_stdio_uart(pico2w_ap_http 0)

# Link Wi-Fi & lwIP networking libraries
target_link_libraries(pico2w_ap_http
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    hardware_uart
)

# Create UF2 output
pico_add_extra_outputs(pico2w_ap_http)
