macro(target_configure_coverage arg)
    if (NOT CMAKE_CROSSCOMPILING)
        message(info "Configured coverage for target ${arg}")
        target_compile_options(${arg}
                PUBLIC
                "-O0"
                "-fprofile-arcs"
                "-ftest-coverage"
                )
        target_link_libraries(${arg} PUBLIC gcov)
        target_link_options(${arg} PUBLIC --coverage)
    endif ()
endmacro()
