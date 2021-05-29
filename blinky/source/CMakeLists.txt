set(APP_NAME blinky)

add_subdirectory(movement)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

    set(SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/platform-controller/stm32l4xx_it.c
    ${CMAKE_CURRENT_LIST_DIR}/platform-controller/stm32l4xx_hal_timebase_TIM.c
    )
    
    find_package(stm32_bsp_iot_node REQUIRED)
    find_package(stm32_runtime_l475_vtg REQUIRED)
    find_package(stm32_hal_l4 REQUIRED)
    
    add_executable(${APP_NAME} ${SOURCES})
    target_link_libraries(${APP_NAME} PRIVATE 
                        stm32_bsp_iot_node::stm32_bsp_iot_node 
                        stm32_runtime_l475_vtg::stm32_runtime_l475_vtg
                        stm32_hal_l4::stm32_hal_l4)
    
    find_package(Platform REQUIRED)
    
    set_target_properties(${APP_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    
    target_setup_runtime(${APP_NAME})
endif()


