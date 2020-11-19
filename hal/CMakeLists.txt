cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(hal C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup()

add_subdirectory(src)

