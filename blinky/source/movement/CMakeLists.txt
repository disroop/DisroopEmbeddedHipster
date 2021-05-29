set(SOURCES 
${CMAKE_CURRENT_LIST_DIR}/rotation.c
${CMAKE_CURRENT_LIST_DIR}/rotation.h
)

add_library(movement STATIC ${SOURCES})
target_include_directories(movement PUBLIC ${CMAKE_CURRENT_LIST_DIR})