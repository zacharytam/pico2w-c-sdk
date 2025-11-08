cmake_minimum_required(VERSION 3.13)

set(PICO_SDK_PATH "/tmp/pico-sdk")
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(PICO_BOARD pico_w)
set(PICO_ENABLE_BINARY_INFO 1)

project(pico2w_lte_router)

pico_sdk_init()

# Main executable
add_executable(pico2w_lte_router
    src/main.c
)

target_link_libraries(pico2w_lte_router 
    pico_stdlib
    hardware_gpio
    hardware_uart
)

# Simple blink executable
add_executable(simple_blink
    src/simple_blink.c
)

target_link_libraries(simple_blink 
    pico_stdlib
    hardware_gpio
)

pico_add_extra_outputs(pico2w_lte_router)
pico_add_extra_outputs(simple_blink)
