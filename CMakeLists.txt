cmake_minimum_required(VERSION 3.13)

# Import Pico SDK
include(pico_sdk_import.cmake)

# Target board
set(PICO_BOARD pico2_w)

project(blink C CXX ASM)
pico_sdk_init()

# Add executable
add_executable(blink
    blink.c
)

# Link libraries
target_link_libraries(blink pico_stdlib)

# For Pico 2 W (Wi-Fi/LED)
if (PICO_CYW43_SUPPORTED)
    target_link_libraries(blink pico_cyw43_arch_none tinyusb_device tinyusb_board)
endif()

# Generate UF2 / map / hex
pico_add_extra_outputs(blink)
