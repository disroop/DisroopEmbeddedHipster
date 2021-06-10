find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(blinky_test
        ${CMAKE_CURRENT_LIST_DIR}/fake_gyro.cpp
        ${CMAKE_CURRENT_LIST_DIR}/fake_gyro.hpp
        ${CMAKE_CURRENT_LIST_DIR}/rotation_test.cpp)
target_link_libraries(blinky_test PUBLIC GTest::gtest GTest::gtest_main movement)
gtest_discover_tests(blinky_test TEST_PREFIX new:)
