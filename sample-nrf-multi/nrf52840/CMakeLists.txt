cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(platform-nrf52840 C ASM)

set(CMAKE_C_STANDARD 99)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if(${DISROOP_BOARD} STREQUAL "NRF52_DK")
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/nrf52dk)
else()
    Message(ERROR " BOARD NEEDS to be supported")
endif()

