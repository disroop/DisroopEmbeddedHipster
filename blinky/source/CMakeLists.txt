add_subdirectory(eiger)
add_subdirectory(movement)
add_subdirectory(indication)
add_subdirectory(coordinator)
add_subdirectory(system)

if (CMAKE_CROSSCOMPILING)
    find_package(stm32_bsp_iot_node REQUIRED)

    add_executable(blinky ${CMAKE_CURRENT_LIST_DIR}/main.c)
    target_link_libraries(blinky PRIVATE eiger movement indication coordinator system stm32_bsp_iot_node::stm32_bsp_iot_node)

    set_target_properties(blinky
            PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

    find_package(stm32_runtime_l475_vtg REQUIRED)
    find_package(Platform REQUIRED)
    target_setup_runtime(blinky)
endif ()


