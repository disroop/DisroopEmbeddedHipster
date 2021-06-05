# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
#Include Conan
include(${CMAKE_CURRENT_BINARY_DIR}/cmake_vars.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
# Set the project name
project(test C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

add_subdirectory(source)


if(NOT CMAKE_CROSSCOMPILING)
    enable_testing()
    add_subdirectory(test)
endif()

#conan profile update settings.compiler.libcxx=libstdc++11 default
