cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(hal C CXX ASM)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup(TARGETS)

include(${CMAKE_CURRENT_LIST_DIR}/cmake/board-settings.cmake)

set(TARGET_NAME ${CONAN_PACKAGE_NAME})
set(NRFSDK nrf5sdk)
SET(SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/config/app_config.h
  ${NRFSDK}/modules/nrfx/mdk/gcc_startup_nrf52840.S 
  ${NRFSDK}/components/boards/boards.c 
  ${NRFSDK}/modules/nrfx/mdk/system_nrf52840.c 
)

SET(INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_LIST_DIR}/config
  ${NRFSDK}/config/nrf52840/config
  ${NRFSDK}/components 
  ${NRFSDK}/integration/nrfx
  ${NRFSDK}/modules/nrfx
  ${NRFSDK}/modules/nrfx/mdk 
  ${NRFSDK}/components/toolchain/cmsis/include
  ${NRFSDK}/modules/nrfx/hal
  ${NRFSDK}/components/libraries/util
  ${NRFSDK}/components/drivers_nrf/nrf_soc_nosd 
  ${NRFSDK}/components/libraries/delay
)

add_library(${TARGET_NAME} STATIC ${SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDE_DIRECTORIES})
target_compile_definitions(${TARGET_NAME} PUBLIC ${COMPILE_DEFINITIONS})