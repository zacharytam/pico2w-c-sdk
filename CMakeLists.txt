cmake_minimum_required(VERSION 3.13)

project(pico2w_ap_http C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Include SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
pico_sdk_init()

# Add executable
add_executable(pico2w_ap_http main.c)

# Add CYW43 include directories
target_include_directories(pico2w_ap_http PRIVATE
    ${PICO_SDK_PATH}/src/rp2_common/pico_cyw43_arch/include
)

# Link libraries
target_link_libraries(pico2w_ap_http
    pico_stdlib
    hardware_gpio
    pico_cyw43_arch_lwip_threadsafe_background
)

# Enable serial and USB output
pico_enable_stdio_usb(pico2w_ap_http 1)
pico_enable_stdio_uart(pico2w_ap_http 1)

# Create .uf2 / .bin outputs
pico_add_extra_outputs(pico2w_ap_http)
