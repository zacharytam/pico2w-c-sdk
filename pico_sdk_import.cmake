# Import the Pico SDK from a relative path
# (the workflow clones it into ${GITHUB_WORKSPACE}/pico-sdk)
set(PICO_SDK_PATH "${CMAKE_CURRENT_LIST_DIR}/pico-sdk")

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)
