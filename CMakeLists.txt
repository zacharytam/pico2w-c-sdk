cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH before including anything
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize project FIRST
project(pico2w_lte_router C CXX ASM)

# Set board BEFORE pico_sdk_init()
set(PICO_BOARD pico_w)

# Initialize SDK
pico_sdk_init()

# Add executable
add_executable(pico2w_lte_router
    src/main.c
)

# Add these lines for proper binary info
pico_set_binary_type(pico2w_lte_router no_flash)
pico_set_binary_name(pico2w_lte_router pico2w_lte_router)

# Link libraries
target_link_libraries(pico2w_lte_router 
    pico_stdlib
    hardware_gpio
    hardware_uart
)

# This must be the LAST command
pico_add_extra_outputs(pico2w_lte_router)

# Force UF2 family ID for RP2040
set(PICO_U2F_FAMILY_ID 0xe48bff56 CACHE INTERNAL "UF2 Family ID")

