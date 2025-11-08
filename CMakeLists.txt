cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set Pico W as the target board
set(PICO_BOARD pico_w)

project(pico2w_lte_router)

pico_sdk_init()

# Add your executable
add_executable(pico2w_lte_router
    src/main.c
)

# Link libraries in the correct order with proper dependencies
target_link_libraries(pico2w_lte_router 
    pico_stdlib
    hardware_uart
    hardware_sync
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip
    pico_mbedtls
    pico_cyw43_driver
)

pico_add_extra_outputs(pico2w_lte_router)
