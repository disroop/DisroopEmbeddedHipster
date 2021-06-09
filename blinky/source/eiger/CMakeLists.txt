add_library(eiger STATIC
        ${CMAKE_CURRENT_LIST_DIR}/scheduler.c
        ${CMAKE_CURRENT_LIST_DIR}/scheduler.h
        ${CMAKE_CURRENT_LIST_DIR}/timer.c
        ${CMAKE_CURRENT_LIST_DIR}/timer.h)
target_include_directories(eiger PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if (NOT CMAKE_CROSSCOMPILING)
    target_compile_options(eiger
            PUBLIC
            "-O0"
            "-fprofile-arcs"
            "-ftest-coverage"
            )
    target_link_libraries(eiger PUBLIC gcov)
    target_link_options(eiger PUBLIC --coverage)
endif ()
             