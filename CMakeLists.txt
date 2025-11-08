cmake_minimum_required(VERSION 3.13)

# Import Pico SDK
include(pico_sdk_import.cmake)

# Project setup
project(blink C CXX ASM)

# Initialize Pico SDK
pico_sdk_init()

# Add executable
add_executable(blink blink.c)
target_link_libraries(blink pico_stdlib)

# Generate UF2 and extra outputs
pico_add_extra_outputs(blink)
