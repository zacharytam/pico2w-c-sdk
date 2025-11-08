cmake_minimum_required(VERSION 3.13)

# Set up project name and SDK
include(pico_sdk_import.cmake)
set(PICO_BOARD pico2w)
project(blink C CXX ASM)
pico_sdk_init()

# Build the blink example
add_executable(blink
    blink.c
)

# Link standard libraries
target_link_libraries(blink pico_stdlib)

# For Pico W support
if (PICO_CYW43_SUPPORTED)
    target_link_libraries(blink pico_cyw43_arch_none)
endif()

# Create UF2, map, etc.
pico_add_extra_outputs(blink)
