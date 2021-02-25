cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(hal C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup(TARGETS)

message(INFO HELLO ${CMAKE_SYSTEM_NAME})
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_subdirectory(src/linux)
else(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_subdirectory(src/nrf)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")


