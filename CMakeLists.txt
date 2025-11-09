cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(pico_w_httpd C CXX ASM)

# Initialize the Pico SDK
pico_sdk_init()

# Set your Wi-Fi credentials
set(WIFI_SSID "MIFI_DBCFF5")
set(WIFI_PASSWORD "1234567890")

# Create the executable
add_executable(pico_w_httpd
    main.c
)

# Pass Wi-Fi credentials as defines
target_compile_definitions(pico_w_httpd PRIVATE
    WIFI_SSID=\"${WIFI_SSID}\"
    WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
)

# Include directories
target_include_directories(pico_w_httpd PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${PICO_LWIP_CONTRIB_PATH}/apps/httpd
)

# Link Pico W and LWIP libraries
target_link_libraries(pico_w_httpd PRIVATE
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_lwip_mdns
    pico_httpd_content
    pico_stdlib
)

# Add generated content library
pico_add_library(pico_httpd_content NOFLAG)
pico_set_lwip_httpd_content(pico_httpd_content INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/content/404.html
    ${CMAKE_CURRENT_LIST_DIR}/content/index.shtml
    ${CMAKE_CURRENT_LIST_DIR}/content/ledpass.shtml
    ${CMAKE_CURRENT_LIST_DIR}/content/ledfail.shtml
    ${CMAKE_CURRENT_LIST_DIR}/content/img/rpi.png.gz
)

# Generate UF2, map, and other outputs
pico_add_extra_outputs(pico_w_httpd)
