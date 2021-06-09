macro(target_configure_coverage target)
    if (NOT CMAKE_CROSSCOMPILING)
        message(info "Configured coverage for target ${arg}")
        target_compile_options(${target}
                PUBLIC
                "-O0"
                "-fprofile-arcs"
                "-ftest-coverage"
                )
        target_link_libraries(${target} PUBLIC gcov)
        target_link_options(${target} PUBLIC --coverage)
    endif ()
endmacro()
