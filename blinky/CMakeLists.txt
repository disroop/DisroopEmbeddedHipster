cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(${CMAKE_CURRENT_BINARY_DIR}/cmake_vars.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(blinky C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

find_package("Coverage" REQUIRED)
#if (NOT CMAKE_CROSSCOMPILING)
#    find_package("CodeAnalysis" REQUIRED)
#endif ()


if (NOT CMAKE_CROSSCOMPILING)
    find_package("CodeAnalysis" REQUIRED)
endif ()

add_subdirectory(source)

if (NOT CMAKE_CROSSCOMPILING)
    enable_testing()
    add_subdirectory(test)
endif ()

#conan profile update settings.compiler.libcxx=libstdc++11 default
