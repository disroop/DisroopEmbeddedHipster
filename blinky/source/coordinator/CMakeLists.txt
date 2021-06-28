add_library(coordinator STATIC
        ${CMAKE_CURRENT_LIST_DIR}/coordinator.c
        ${CMAKE_CURRENT_LIST_DIR}/coordinator.h)
target_include_directories(coordinator PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(coordinator PUBLIC eiger indication movement)
target_configure_coverage(coordinator)