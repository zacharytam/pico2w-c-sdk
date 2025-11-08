cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico2w_lte_router C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(pico2w_lte_router
    src/main.c
)

pico_enable_stdio_usb(pico2w_lte_router 1)
pico_enable_stdio_uart(pico2w_lte_router 0)

target_link_libraries(pico2w_lte_router
    pico_stdlib
    pico_cyw43_arch
    lwip
)

pico_add_extra_outputs(pico2w_lte_router)
