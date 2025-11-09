cmake_minimum_required(VERSION 3.12)

# Import Pico SDK directly from external folder
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico2w_ap_http C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize Pico SDK
pico_sdk_init()

# Add your source file
add_executable(pico2w_ap_http main.c)

# Link required libraries
target_link_libraries(pico2w_ap_http
    pico_stdlib
    hardware_gpio
    cyw43_driver
)

# Enable USB and UART output
pico_enable_stdio_usb(pico2w_ap_http 1)
pico_enable_stdio_uart(pico2w_ap_http 1)

# Generate UF2
pico_add_extra_outputs(pico2w_ap_http)
