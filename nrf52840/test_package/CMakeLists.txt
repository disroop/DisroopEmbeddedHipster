cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(tst C)

set(CMAKE_C_STANDARD 99)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup()

set(TARGET_NAME ${PROJECT_NAME}_app)

add_executable(${TARGET_NAME} main.c)
target_link_libraries(${TARGET_NAME} PUBLIC ${CONAN_LIBS})

find_package(Platform)
if(PLATFORM_FOUND)
    target_setup_runtime(${TARGET_NAME})
endif(PLATFORM_FOUND) 

