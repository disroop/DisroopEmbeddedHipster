set(SOURCES 
${CMAKE_CURRENT_LIST_DIR}/coordinator.c
${CMAKE_CURRENT_LIST_DIR}/coordinator.h
)

add_library(coordinator STATIC ${SOURCES})
target_include_directories(coordinator PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(coordinator PRIVATE eiger indication movement)