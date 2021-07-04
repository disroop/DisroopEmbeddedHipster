add_library(blinky STATIC
        ${CMAKE_CURRENT_LIST_DIR}/blinky.c
        ${CMAKE_CURRENT_LIST_DIR}/blinky.h)
target_include_directories(blinky PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(blinky PUBLIC eiger indication movement)
target_configure_coverage(blinky)