add_executable(coordinator_test ${CMAKE_CURRENT_LIST_DIR}/coordinator_test.cpp)
target_link_libraries(coordinator_test PUBLIC GTest::gtest GTest::gtest_main coordinator)
gtest_discover_tests(coordinator_test TEST_PREFIX new:)
