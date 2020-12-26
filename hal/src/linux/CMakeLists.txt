set(LIBRARY_NAME hal-linux)

set(SOURCES
        ${CMAKE_SOURCE_DIR}/include/Hal.hpp
        ${CMAKE_CURRENT_LIST_DIR}/HalLinux.cpp
        ${CMAKE_CURRENT_LIST_DIR}/HalLinux.hpp)

add_library(${LIBRARY_NAME} STATIC ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})





