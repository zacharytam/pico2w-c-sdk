# ---- Minimum CMake version and SDK import ----
cmake_minimum_required(VERSION 3.13)

# Import the Pico SDK (make sure PICO_SDK_PATH is set in your workflow)
include(pico_sdk_import.cmake)

# ---- Project setup ----
project(pico2w_ap_http C CXX ASM)
pico_sdk_init()

# ---- Your source files ----
add_executable(pico2w_ap_http
    main.c
)

# ---- Link libraries ----
# - pico_stdlib: core SDK functions (GPIO, UART, etc.)
# - pico_cyw43_arch_lwip_threadsafe_background: Wi-Fi + lwIP (thread-safe background mode)
target_link_libraries(pico2w_ap_http
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

# ---- Optional: enable stdio over USB or UART ----
pico_enable_stdio_usb(pico2w_ap_http 1)
pico_enable_stdio_uart(pico2w_ap_http 0)

# ---- Generate additional output formats (.uf2, .bin, .hex) ----
pico_add_extra_outputs(pico2w_ap_http)
