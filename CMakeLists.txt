cmake_minimum_required(VERSION 3.13)

# Initialize project FIRST
project(pico2w_lte_router C CXX ASM)

# Set PICO_SDK_PATH
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize SDK
pico_sdk_init()

# Set target board
set(PICO_BOARD pico_w)

# Add main executable
add_executable(pico2w_lte_router
    src/main.c
)

# Link libraries - CRITICAL: Use pico_cyw43_arch_none for Pico W
target_link_libraries(pico2w_lte_router 
    pico_stdlib
    pico_cyw43_arch_none
)

# Add extra outputs (UF2, etc)
pico_add_extra_outputs(pico2w_lte_router)

# Set program URL - this adds binary info needed for auto-reboot
pico_set_program_url(pico2w_lte_router "https://github.com/zacharytam/pico2w-c-sdk")
