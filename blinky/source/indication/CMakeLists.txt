add_library(indication STATIC
        ${CMAKE_CURRENT_LIST_DIR}/indication.c
        ${CMAKE_CURRENT_LIST_DIR}/indication.h)
target_include_directories(indication PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if (NOT CMAKE_CROSSCOMPILING)
    target_compile_options(indication
            PUBLIC
            "-O0"
            "-fprofile-arcs"
            "-ftest-coverage"
            )
    target_link_libraries(indication PUBLIC gcov)
    target_link_options(indication PUBLIC --coverage)
endif ()
             