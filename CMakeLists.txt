cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set Pico W as the target board
set(PICO_BOARD pico_w)

project(pico2w_lte_router)

pico_sdk_init()

# Enable binary information
set(PICO_ENABLE_BINARY_INFO 1)

# Add your executable
add_executable(pico2w_lte_router
    src/main.c
)

# Set binary name explicitly
pico_set_binary_name(pico2w_lte_router pico2w_lte_router)

# Link libraries
target_link_libraries(pico2w_lte_router 
    pico_stdlib
    hardware_gpio
    hardware_uart
)

# This MUST be the last command
pico_add_extra_outputs(pico2w_lte_router)
