# set(QUIC_CODE_CHECK)
# if(QUIC_CODE_CHECK)
if (True)
    # clang-tidy ######################################################################
    find_program(CLANGTIDY NAMES clang-tidy)
    if (CLANGTIDY)
        message(Info "Found clang-tidy: ${CLANGTIDY}")
        set(CLANG_TIDY_CHECKS *
                # add checks to ignore here:
                -android-cloexec-fopen
                -bugprone-macro-parentheses
                -bugprone-sizeof-expression
                -clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
                -clang-diagnostic-microsoft-anon-tag
                -cppcoreguidelines-avoid-magic-numbers
                -cppcoreguidelines-avoid-non-const-global-variables
                -cppcoreguidelines-init-variables
                -google-readability-todo
                -hicpp-no-assembler
                -hicpp-signed-bitwise
                -llvmlibc-restrict-system-libc-headers
                -misc-no-recursion # do you really need recursion?
                -readability-avoid-const-params-in-decls
                -readability-isolate-declaration
                -readability-magic-numbers
                -readability-non-const-parameter
                )
        string(REPLACE ";" "," CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS}")
        set(CMAKE_C_CLANG_TIDY_AVAILABLE ${CLANGTIDY} -checks=${CLANG_TIDY_CHECKS}
                -system-headers --warnings-as-errors=*)
    else ()
        message(INFO "clang-tidy not found")
    endif ()

    # cpplint ######################################################################
    find_program(CPPLINT_PATH NAMES cpplint)
    if (CPPLINT_PATH)
        message(STATUS "Looking for CppLint - found")
        set(CPPLINT_OPTS
                ${CPPLINT_PATH}
                "--linelength=79"
                )
        set(CMAKE_C_CPPLINT "${CPPLINT_OPTS}")
        set(CMAKE_CXX_CPPLINT "${CPPLINT_OPTS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ferror-limit=0")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ferror-limit=0")
    else ()
        message(STATUS "Looking for CppLint - not found")
    endif ()

    # cppcheck ######################################################################
    find_program(CPPCHECK NAMES cppcheck)
    if (CPPCHECK)
        message(INFO "Found cppcheck: ${CPPCHECK}")
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
    endif ()

    # find_program(CPPCHECK NAMES cppcheck)
    # if(CPPCHECK)
    #     message(INFO "Found cppcheck: ${CPPCHECK}")
    #     set(CMAKE_C_CPPCHECK ${CPPCHECK} -q --inline-suppr
    #         --suppress=duplicateValueTernary --suppress=objectIndex
    #         --suppress=varFuncNullUB
    #         # these are finding potential logic issues, may want to suppress when focusing on nits:
    #         --suppress=nullPointer --suppress=nullPointerRedundantCheck
    #         --enable=warning,style,performance,portability -D__linux__)
    # else()
    #     message(INFO "cppcheck not found")
    # endif()
    if (CMAKE_C_COMPILER_ID MATCHES "Clang" AND
            CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        # Use clang-tidy for extra warnings, if it's installed
        find_program(CLANGTIDY NAMES clang-tidy)
        if (CLANGTIDY)
            message(STATUS "Found clang-tidy: ${CLANGTIDY}")
            # set(CLANG_TIDY_CHECKS *
            #         -altera-struct-pack-align
            #         -bugprone-narrowing-conversions
            #         -cert-err58-cpp
            #         -clang-diagnostic-tautological-value-range-compare
            #         -concurrency-mt-unsafe
            #         -cppcoreguidelines-avoid-magic-numbers
            #         -cppcoreguidelines-avoid-non-const-global-variables
            #         -cppcoreguidelines-init-variables
            #         -cppcoreguidelines-macro-usage
            #         -cppcoreguidelines-narrowing-conversions
            #         -cppcoreguidelines-owning-memory
            #         -cppcoreguidelines-pro-bounds-array-to-pointer-decay
            #         -cppcoreguidelines-pro-bounds-constant-array-index
            #         -cppcoreguidelines-pro-bounds-pointer-arithmetic
            #         -cppcoreguidelines-pro-type-vararg
            #         -fuchsia-statically-constructed-objects
            #         -google-readability-braces-around-statements
            #         -google-readability-todo
            #         -google-runtime-references
            #         -hicpp-braces-around-statements
            #         -hicpp-multiway-paths-covered
            #         -hicpp-no-array-decay
            #         -hicpp-signed-bitwise
            #         -hicpp-vararg
            #         -llvmlibc-callee-namespace
            #         -llvmlibc-implementation-in-namespace
            #         -llvmlibc-restrict-system-libc-headers
            #         -modernize-use-trailing-return-type
            #         -performance-no-int-to-ptr
            #         -readability-braces-around-statements
            #         -readability-function-cognitive-complexity
            #         -readability-magic-numbers
            #         -readability-misleading-indentation
            #         )
            # string(REPLACE ";" "," CLANG_TIDY_CHECKS "${CLANG_TIDY_CHECKS}")
            set(CMAKE_C_CLANG_TIDY ${CLANGTIDY}
                    -system-headers -checks=${CLANG_TIDY_CHECKS} --warnings-as-errors=*
                    )
            set(CMAKE_CXX_CLANG_TIDY ${CMAKE_C_CLANG_TIDY})
        endif ()
    endif ()
endif ()

# include-what-you-use iwyu ######################################################################
if (NOT CMAKE_CROSSCOMPILING)
    find_program(iwyu_path NAMES include-what-you-use iwyu)
    if (NOT iwyu_path)
        message(FATAL_ERROR "Could not find the program include-what-you-use")
    endif ()

    set(CMAKE_C_INCLUDE_WHAT_YOU_USE include-what-you-use)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE include-what-you-use)
endif ()

function(foo)
    message(INFO "asdf")
endfunction()