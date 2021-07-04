add_executable(movement_internal_test
        ${CMAKE_CURRENT_LIST_DIR}/rotation_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tracker_test.cpp)
target_link_libraries(movement_internal_test PUBLIC GTest::gtest GTest::gtest_main movement)
gtest_discover_tests(movement_internal_test TEST_PREFIX new:)
