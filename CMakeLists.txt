cmake_minimum_required(VERSION 3.13)

# Import the Pico SDK
include(pico_sdk_import.cmake)

# Set target board to Pico 2 W
set(PICO_BOARD pico2_w)

# Project definition
project(blink C CXX ASM)

# Initialize the SDK
pico_sdk_init()

# Add executable
add_executable(blink
    blink.c
)

# Link standard Pico libraries
target_link_libraries(blink pico_stdlib)

# Link Wi-Fi driver if available
if (PICO_CYW43_SUPPORTED)
    target_link_libraries(blink pico_cyw43_arch_none)
endif()

# Generate UF2 / map / hex files
pico_add_extra_outputs(blink)
