add_library(indication STATIC
        ${CMAKE_CURRENT_LIST_DIR}/indication.c
        ${CMAKE_CURRENT_LIST_DIR}/indication.h)
target_include_directories(indication PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_configure_coverage(indication)