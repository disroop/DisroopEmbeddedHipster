set(SOURCES 
${CMAKE_CURRENT_LIST_DIR}/rotation.c
${CMAKE_CURRENT_LIST_DIR}/rotation.h
${CMAKE_CURRENT_LIST_DIR}/tracker.c
${CMAKE_CURRENT_LIST_DIR}/tracker.h
)

add_library(movement STATIC ${SOURCES})
target_include_directories(movement PUBLIC ${CMAKE_CURRENT_LIST_DIR})