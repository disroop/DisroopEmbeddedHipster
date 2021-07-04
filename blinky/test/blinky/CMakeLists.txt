add_executable(blinky_test ${CMAKE_CURRENT_LIST_DIR}/blinky_test.cpp)
target_link_libraries(blinky_test PUBLIC GTest::gtest GTest::gtest_main blinky)
gtest_discover_tests(blinky_test TEST_PREFIX new:)
