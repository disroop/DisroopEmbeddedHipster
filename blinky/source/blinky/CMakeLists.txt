add_library(blinky STATIC
        ${CMAKE_CURRENT_LIST_DIR}/blinky.c
        ${CMAKE_CURRENT_LIST_DIR}/blinky.h)

get_target_property(INDICATION_INCLUDES indication INCLUDE_DIRECTORIES)
get_target_property(MOVEMENT_INCLUDES movement INCLUDE_DIRECTORIES)
get_target_property(EIGER_INCLUDES eiger INCLUDE_DIRECTORIES)

target_include_directories(blinky PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${INDICATION_INCLUDES} ${MOVEMENT_INCLUDES} ${EIGER_INCLUDES})
target_link_libraries(blinky PRIVATE eiger indication movement)
target_configure_coverage(blinky)