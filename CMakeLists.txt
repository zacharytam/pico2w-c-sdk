cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH before anything else
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Initialize project
project(pico2w_lte_router)

# Set board before SDK init
set(PICO_BOARD pico_w)

# Initialize SDK
pico_sdk_init()

# Add executable
add_executable(pico2w_lte_router
    src/main.c
)

# Link libraries
target_link_libraries(pico2w_lte_router 
    pico_stdlib
    pico_cyw43_arch_none
)

# Add outputs
pico_add_extra_outputs(pico2w_lte_router)

# Add URL for binary info
pico_set_program_url(pico2w_lte_router "https://github.com/zacharytam/pico2w-c-sdk")
