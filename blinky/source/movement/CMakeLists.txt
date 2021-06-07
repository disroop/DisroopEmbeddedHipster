set(LIB_NAME movement)
set(SOURCES 
${CMAKE_CURRENT_LIST_DIR}/movement.c
${CMAKE_CURRENT_LIST_DIR}/movement.h
${CMAKE_CURRENT_LIST_DIR}/internal/rotation.c
${CMAKE_CURRENT_LIST_DIR}/internal/rotation.h
${CMAKE_CURRENT_LIST_DIR}/internal/tracker.c
${CMAKE_CURRENT_LIST_DIR}/internal/tracker.h)

add_library(${LIB_NAME} STATIC ${SOURCES})
target_include_directories(${LIB_NAME} 
                            PUBLIC ${CMAKE_CURRENT_LIST_DIR})

                            
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
                    
                    