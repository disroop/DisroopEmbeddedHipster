include(${CMAKE_CURRENT_LIST_DIR}/cmake/board-settings.cmake)
set(SDK_ROOT ${CMAKE_CURRENT_BINARY_DIR}/../nrf5sdk/nrf5sdk)

set(TARGET_NAME ${PROJECT_NAME})

SET(SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/config/app_config.h
  ${SDK_ROOT}/modules/nrfx/mdk/gcc_startup_nrf52840.S 
  ${SDK_ROOT}/components/boards/boards.c 
  ${SDK_ROOT}/modules/nrfx/mdk/system_nrf52840.c 
)

SET(INCLUDE_DIRECTORIES
  ${CMAKE_CURRENT_LIST_DIR}/config
  ${SDK_ROOT}/config/nrf52840/config
  ${SDK_ROOT}/components 
  ${SDK_ROOT}/integration/nrfx
  ${SDK_ROOT}/modules/nrfx
  ${SDK_ROOT}/modules/nrfx/mdk 
  ${SDK_ROOT}/components/toolchain/cmsis/include
  ${SDK_ROOT}/modules/nrfx/hal
  ${SDK_ROOT}/components/libraries/util
  ${SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd 
  ${SDK_ROOT}/components/libraries/delay
)

add_library(${TARGET_NAME} STATIC ${SOURCES})
target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDE_DIRECTORIES})
target_compile_definitions(${TARGET_NAME} PUBLIC ${COMPILE_DEFINITIONS})
