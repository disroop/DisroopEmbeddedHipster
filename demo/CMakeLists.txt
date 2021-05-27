cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(demo C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake_vars.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)

add_subdirectory(src)

if(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Generic")
    enable_testing()
    add_subdirectory(test)
endif(NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Generic")