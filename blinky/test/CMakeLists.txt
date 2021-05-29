find_package(GTest REQUIRED)
include(GoogleTest)

SET(TARGET "blinky")

set(SOURCES
${CMAKE_CURRENT_LIST_DIR}/fake_gyro.cpp
${CMAKE_CURRENT_LIST_DIR}/fake_gyro.hpp
${CMAKE_CURRENT_LIST_DIR}/test_rotation.cpp
)

add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} PUBLIC GTest::gtest GTest::gtest_main movement)
add_test(${TARGET}_test ${TARGET})