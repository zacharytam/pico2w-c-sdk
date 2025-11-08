# Import Pico SDK from the path provided by workflow
# This file tells CMake where to find the SDK
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
