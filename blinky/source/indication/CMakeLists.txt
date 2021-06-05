set(SOURCES 
${CMAKE_CURRENT_LIST_DIR}/indication.c
${CMAKE_CURRENT_LIST_DIR}/indication.h
)

add_library(indication STATIC ${SOURCES})
target_include_directories(indication PUBLIC ${CMAKE_CURRENT_LIST_DIR})