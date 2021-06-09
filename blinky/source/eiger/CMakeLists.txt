add_library(eiger STATIC
        ${CMAKE_CURRENT_LIST_DIR}/scheduler.c
        ${CMAKE_CURRENT_LIST_DIR}/scheduler.h
        ${CMAKE_CURRENT_LIST_DIR}/timer.c
        ${CMAKE_CURRENT_LIST_DIR}/timer.h)
target_include_directories(eiger PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_configure_coverage(eiger)