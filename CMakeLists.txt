cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize project
project(blink)

# Set board
set(PICO_BOARD pico_w)

# Initialize SDK
pico_sdk_init()

# Add executable
add_executable(blink
    src/official_blink.c
)

# Pull in common dependencies
target_link_libraries(blink pico_stdlib)

# Use CYW43 arch for Pico W
if (PICO_BOARD STREQUAL "pico_w")
    target_link_libraries(blink pico_cyw43_arch_none)
endif()

# Create map/bin/hex file etc.
pico_add_extra_outputs(blink)

# Add URL - use the same function as official examples
pico_set_program_url(blink "https://github.com/raspberrypi/pico-examples")
