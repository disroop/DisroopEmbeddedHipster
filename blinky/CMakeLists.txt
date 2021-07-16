cmake_minimum_required(VERSION 3.16 FATAL_ERROR)


include(${CMAKE_CURRENT_BINARY_DIR}/conan_toolchain.cmake)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(blinky_app C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

find_package("Coverage" REQUIRED)
#if (NOT CMAKE_CROSSCOMPILING)
#    find_package("CodeAnalysis" REQUIRED)
#endif ()


if (NOT CMAKE_CROSSCOMPILING)
    find_package("CodeAnalysis" REQUIRED)
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(source)

if (NOT CMAKE_CROSSCOMPILING)
    enable_testing()
    add_subdirectory(test)
endif ()

add_custom_target(graphviz 
                  "${CMAKE_COMMAND}" "--graphviz=cmake-target-graph.dot" .
                  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

#conan profile update settings.compiler.libcxx=libstdc++11 default
