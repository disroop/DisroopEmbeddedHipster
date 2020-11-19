set(TARGET_NAME blinky_app)

set(SOURCES
        LedStrip.cpp
        LedStrip.hpp)
add_library(visual-obj OBJECT ${SOURCES})

target_include_directories(visual-obj PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Generic")
        add_executable(${TARGET_NAME} main_target.cpp $<TARGET_OBJECTS:visual-obj>)
        target_link_libraries(${TARGET_NAME} PUBLIC ${CONAN_LIBS})
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Generic")

find_package(Platform)
if(PLATFORM_FOUND)
    target_setup_runtime(${TARGET_NAME})
else(PLATFORM_FOUND)
    Message(WARNING " Message: Baremetal PLatform will be used.")
endif(PLATFORM_FOUND) 


