cmake_minimum_required(VERSION 3.13)

# Set PICO_SDK_PATH
set(PICO_SDK_PATH "/tmp/pico-sdk")

# Import Pico SDK
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set Pico W as the target board
set(PICO_BOARD pico_w)

project(pico2w_lte_router)

pico_sdk_init()

# Add executable
add_executable(pico2w_lte_router
    src/main.c
)

# Pull in common dependencies
target_link_libraries(pico2w_lte_router pico_stdlib)

# Use the correct CYW43 arch for Pico W
if (PICO_BOARD STREQUAL "pico_w")
    target_link_libraries(pico2w_lte_router pico_cyw43_arch_none)
endif()

# Create map/bin/hex file etc.
pico_add_extra_outputs(pico2w_lte_router)

# Add URL via pico_set_program_url (this adds the binary info needed for auto-reboot)
pico_set_program_url(pico2w_lte_router "https://github.com/zacharytam/pico2w-c-sdk")
