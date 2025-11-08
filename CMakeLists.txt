cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set Pico W as the target board - MUST be before project()
set(PICO_BOARD pico_w)

# Initialize project
project(pico2w_lte_router C CXX ASM)

# Initialize SDK - this sets up proper binary info
pico_sdk_init()

# Add executables
add_executable(pico2w_lte_router
    src/main.c
)

add_executable(simple_blink
    src/simple_blink.c
)

# Link libraries for both
target_link_libraries(pico2w_lte_router 
    pico_stdlib
    hardware_gpio
    hardware_uart
)

target_link_libraries(simple_blink 
    pico_stdlib
    hardware_gpio
)

# Add extra outputs (UF2, etc) - MUST be last
pico_add_extra_outputs(pico2w_lte_router)
pico_add_extra_outputs(simple_blink)
