set(LIBRARY_NAME hal)

set(SOURCES 
        ${CMAKE_CURRENT_LIST_DIR}/Hal.hpp
        ${CMAKE_CURRENT_LIST_DIR}/HalNrf.cpp
        ${CMAKE_CURRENT_LIST_DIR}/HalNrf.hpp)
add_library(${LIBRARY_NAME} STATIC ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${CONAN_INCLUDE_DIRS})

find_package(Platform)
if(PLATFORM_FOUND)
    target_add_compile_definitions(${LIBRARY_NAME})  
endif(PLATFORM_FOUND)





