add_library(coordinator STATIC
        ${CMAKE_CURRENT_LIST_DIR}/coordinator.c
        ${CMAKE_CURRENT_LIST_DIR}/coordinator.h)
target_include_directories(coordinator PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(coordinator PRIVATE eiger indication movement)

if (NOT CMAKE_CROSSCOMPILING)
    target_compile_options(coordinator
            PUBLIC
            "-O0"
            "-fprofile-arcs"
            "-ftest-coverage"
            )
    target_link_libraries(coordinator PUBLIC gcov)
    target_link_options(coordinator PUBLIC --coverage)
endif ()
             