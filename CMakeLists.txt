cmake_minimum_required(VERSION 3.13)

# --- Define project ---
project(pico2w_ap_http C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# --- Point directly to the SDK import file ---
# (This uses the PICO_SDK_PATH from your GitHub Actions environment)
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# --- Initialize the SDK ---
pico_sdk_init()

# --- Add executable ---
add_executable(pico2w_ap_http main.c)

# --- Link with standard Pico + Wi-Fi stack ---
target_link_libraries(pico2w_ap_http
    pico_stdlib
    hardware_gpio
    pico_cyw43_arch_lwip_threadsafe_background
)

# --- Enable serial and USB output ---
pico_enable_stdio_usb(pico2w_ap_http 1)
pico_enable_stdio_uart(pico2w_ap_http 1)

# --- Create .uf2 / .bin outputs ---
pico_add_extra_outputs(pico2w_ap_http)
