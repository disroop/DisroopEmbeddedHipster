set(RUN_CODE_ANALYSIS)
if(RUN_CODE_ANALYSIS)
    # include-what-you-use iwyu ######################################################################
    find_program(IWYU NAMES include-what-you-use iwyu)
    if (IWYU)
        message(Info " CodeAnalysis: Found include-what-you-us: ${IWYU}")
        set(CMAKE_C_INCLUDE_WHAT_YOU_USE include-what-you-use)
        set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)
    else ()
        message(FATAL_ERROR " CodeAnalysis: include-what-you-use not found")
    endif ()

    # clang-tidy ######################################################################
    find_program(CLANGTIDY NAMES clang-tidy)
    if (CLANGTIDY)
        message(Info " CodeAnalysis: Found clang-tidy: ${CLANGTIDY}")
        # checks are configured in .clang-tidy
        set(CMAKE_C_CLANG_TIDY ${CLANGTIDY} -system-headers --warnings-as-errors=*)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY} -system-headers --warnings-as-errors=*)
    else ()
        message(FATAL_ERROR " CodeAnalysis: clang-tidy not found")
    endif ()

    # cpplint ######################################################################
    find_program(CPPLINT_PATH NAMES cpplint)
    if (CPPLINT_PATH)
        message(STATUS " CodeAnalysis: Found for CppLint: ${CPPLINT_PATH}")
        set(CPPLINT_OPTS
                ${CPPLINT_PATH}
                "--linelength=79"
                )
        set(CMAKE_C_CPPLINT "${CPPLINT_OPTS}")
        set(CMAKE_CXX_CPPLINT "${CPPLINT_OPTS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ferror-limit=0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=0")
    else ()
        message(FATAL_ERROR " CodeAnalysis: CppLint - not found")
    endif ()

    # cppcheck ######################################################################
    find_program(CPPCHECK NAMES cppcheck)
    if (CPPCHECK)
        message(INFO " CodeAnalysis: Found cppcheck: ${CPPCHECK}")
        set(CMAKE_C_CPPCHECK ${CPPCHECK} -q --inline-suppr
                --enable=all
                --suppress=duplicateValueTernary
                --suppress=missingInclude
                --suppress=missingIncludeSystem
                --suppress=unmatchedSuppression
                --suppress=unusedFunction
                --error-exitcode=2
                -I ${PROJECT_SOURCE_DIR}/lib/include
                -I ${PROJECT_SOURCE_DIR}/lib/deps/warpcore/lib/include
                )
        set(CMAKE_CXX_CPPCHECK ${CMAKE_C_CPPCHECK})
    else ()
        message(FATAL_ERROR " CodeAnalysis: cppcheck - not found")
    endif ()

endif ()

