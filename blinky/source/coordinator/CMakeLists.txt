set(LIB_NAME coordinator)

set(SOURCES 
${CMAKE_CURRENT_LIST_DIR}/coordinator.c
${CMAKE_CURRENT_LIST_DIR}/coordinator.h
)

add_library(${LIB_NAME} STATIC ${SOURCES})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${LIB_NAME} PRIVATE eiger indication movement)

if(NOT CMAKE_CROSSCOMPILING)
    target_compile_options(${LIB_NAME}
        PUBLIC
        "-O0"
        "-fprofile-arcs"
        "-ftest-coverage"
    )
    target_link_libraries(${LIB_NAME} PUBLIC gcov)
    target_link_options(${LIB_NAME} PUBLIC --coverage)
endif()
             