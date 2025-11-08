cmake_minimum_required(VERSION 3.13)  # or 3.31

# Import Pico SDK
include(pico_sdk_import.cmake)

# Define board and project
set(PICO_BOARD pico2)
project(blink C CXX ASM)

# Initialize Pico SDK
pico_sdk_init()

# Add executable
add_executable(blink blink.c)

# Link standard Pico libraries
target_link_libraries(blink pico_stdlib)

# Generate UF2 and map/bin outputs
pico_add_extra_outputs(blink)
