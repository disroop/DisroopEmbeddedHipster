set(APP_NAME test)

set(SOURCES
${CMAKE_CURRENT_LIST_DIR}/main.c
${CMAKE_CURRENT_LIST_DIR}/platform/stm32l4xx_it.c
${CMAKE_CURRENT_LIST_DIR}/platform/stm32l4xx_it.h
${CMAKE_CURRENT_LIST_DIR}/platform/system_stm32l4xx.c
${CMAKE_CURRENT_LIST_DIR}/platform/syscalls.c
${CMAKE_CURRENT_LIST_DIR}/platform/stm32l4xx_hal_timebase_TIM.c
)

find_package(stm32_bsp_iot_node REQUIRED)
find_package(stm32_runtime_l475 REQUIRED)
find_package(stm32_hal_l4 REQUIRED)
set(LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/platform/STM32L475VGTx_FLASH.ld)

add_executable(${APP_NAME} ${SOURCES})
target_link_libraries(${APP_NAME} PRIVATE stm32_bsp_iot_node::stm32_bsp_iot_node stm32_runtime_l475::stm32_runtime_l475 stm32_hal_l4::stm32_hal_l4)

target_link_options(${APP_NAME} PRIVATE -T ${LINKER_SCRIPT} -Xlinker -Map=${APP_NAME}.map)
