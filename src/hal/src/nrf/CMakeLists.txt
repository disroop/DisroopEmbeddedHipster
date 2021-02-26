set(LIBRARY_NAME halnrf)

set(SOURCES_NRF
        ${CMAKE_CURRENT_LIST_DIR}/../../include/Hal.hpp
        ${CMAKE_CURRENT_LIST_DIR}/../../include/HalNrf.hpp
        ${CMAKE_CURRENT_LIST_DIR}/HalNrf.cpp)

add_library(${LIBRARY_NAME} STATIC ${SOURCES_NRF})

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../include )
conan_target_link_libraries(${LIBRARY_NAME})





