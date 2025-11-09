cmake_minimum_required(VERSION 3.12)

# Pull in Pico SDK
include($ENV{PICO_SDK_PATH}/pico_sdk_import.cmake)

project(pico2w_ap_http C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add the CYW43 driver
add_subdirectory($ENV{CYW43_DRIVER_PATH} cyw43-driver)

# Add your executable
add_executable(pico2w_ap_http main.c)

# Link against Pico SDK libraries and CYW43 driver
target_link_libraries(pico2w_ap_http
    pico_stdlib
    hardware_gpio
    cyw43_driver
)

# Enable USB/serial output
pico_enable_stdio_usb(pico2w_ap_http 1)
pico_enable_stdio_uart(pico2w_ap_http 1)

# Create UF2
pico_add_extra_outputs(pico2w_ap_http)
