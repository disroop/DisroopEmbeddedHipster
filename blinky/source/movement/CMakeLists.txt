set(SOURCES 
${CMAKE_CURRENT_LIST_DIR}/movement.c
${CMAKE_CURRENT_LIST_DIR}/movement.h
${CMAKE_CURRENT_LIST_DIR}/internal/rotation.c
${CMAKE_CURRENT_LIST_DIR}/internal/rotation.h
${CMAKE_CURRENT_LIST_DIR}/internal/tracker.c
${CMAKE_CURRENT_LIST_DIR}/internal/tracker.h)

add_library(movement STATIC ${SOURCES})
target_include_directories(movement 
                            PUBLIC ${CMAKE_CURRENT_LIST_DIR})