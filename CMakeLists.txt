cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set Pico W as the target board
set(PICO_BOARD pico_w)

# FORCE UF2 FAMILY ID - This is critical for auto-reboot
set(PICO_U2F_FAMILY_ID 0xe48bff56 CACHE INTERNAL "UF2 Family ID")

project(pico2w_lte_router)

pico_sdk_init()

# Add your executable
add_executable(pico2w_lte_router
    src/main.c
)

# Set binary name and type
pico_set_binary_name(pico2w_lte_router pico2w_lte_router)
pico_set_binary_type(pico2w_lte_router no_flash)

# Link libraries
target_link_libraries(pico2w_lte_router 
    pico_stdlib
    hardware_gpio
    hardware_uart
)

# This MUST be the last command
pico_add_extra_outputs(pico2w_lte_router)
