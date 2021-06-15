set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(eiger)
add_subdirectory(movement)
add_subdirectory(indication)
add_subdirectory(coordinator)

if (CMAKE_CROSSCOMPILING)
    add_subdirectory(system)
    find_package(stm32_bsp_iot_node REQUIRED)

    add_executable(blinky ${CMAKE_CURRENT_LIST_DIR}/main.c)
    target_link_libraries(blinky PRIVATE eiger movement indication coordinator system stm32_bsp_iot_node::stm32_bsp_iot_node )

    find_package(stm32_runtime_l475_vtg REQUIRED)
    find_package(Platform REQUIRED)
    set(LINKER_FLAGS LINKER:--whole-archive -lsystem LINKER:--no-whole-archive)
    target_setup_runtime_flags(blinky "${LINKER_FLAGS}")
endif ()


