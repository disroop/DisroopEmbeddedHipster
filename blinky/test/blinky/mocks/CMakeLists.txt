add_library(movement_fake STATIC
        ${CMAKE_CURRENT_LIST_DIR}/movement_fake.c
        ${CMAKE_CURRENT_LIST_DIR}/movement_fake.h)

get_target_property(MOVEMENT_INCLUDES movement INCLUDE_DIRECTORIES)
target_include_directories(movement_fake 
                    PUBLIC ${CMAKE_CURRENT_LIST_DIR}
                    PRIVATE ${MOVEMENT_INCLUDES})

get_target_property(INDICATION_INCLUDES indication INCLUDE_DIRECTORIES)
add_library(indication_fake STATIC
        ${CMAKE_CURRENT_LIST_DIR}/indication_fake.c
        ${CMAKE_CURRENT_LIST_DIR}/indication_fake.h)

target_include_directories(indication_fake 
                        PUBLIC ${CMAKE_CURRENT_LIST_DIR} 
                        PRIVATE ${INDICATION_INCLUDES})