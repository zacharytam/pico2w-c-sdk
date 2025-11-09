cmake_minimum_required(VERSION 3.13)

# Import SDK and Extras
include(pico_sdk_import.cmake)
include(pico_extras_import.cmake)

project(pico2w_ap_http C CXX ASM)

pico_sdk_init()

add_executable(pico2w_ap_http main.c)

target_link_libraries(pico2w_ap_http
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_add_extra_outputs(pico2w_ap_http)
