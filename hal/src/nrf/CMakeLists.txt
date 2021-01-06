set(LIBRARY_NAME halnrf)

set(SOURCES_NRF
        ${CMAKE_SOURCE_DIR}/include/Hal.hpp
        ${CMAKE_SOURCE_DIR}/include/HalNrf.hpp
        ${CMAKE_CURRENT_LIST_DIR}/HalNrf.cpp)

add_library(${LIBRARY_NAME} STATIC ${SOURCES_NRF})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${LIBRARY_NAME} PUBLIC CONAN_PKG::platformnrf52840)
find_package(Platform)
if(PLATFORM_FOUND)
    target_add_compile_definitions(${LIBRARY_NAME})  
endif(PLATFORM_FOUND)





