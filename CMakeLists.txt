cmake_minimum_required(VERSION 3.13)

# --- Define project ---
project(pico2w_ap_http C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# --- Locate the SDK import file ---
if (DEFINED PICO_SDK_PATH)
    message(STATUS "Using PICO_SDK_PATH from environment: ${PICO_SDK_PATH}")
    include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
elseif (EXISTS "${CMAKE_CURRENT_LIST_DIR}/pico-sdk/external/pico_sdk_import.cmake")
    message(STATUS "Using local pico-sdk folder")
    include(${CMAKE_CURRENT_LIST_DIR}/pico-sdk/external/pico_sdk_import.cmake)
else()
    message(FATAL_ERROR "pico_sdk_import.cmake not found! Please set PICO_SDK_PATH.")
endif()

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
