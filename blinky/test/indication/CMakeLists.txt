add_executable(indication_test
        ${CMAKE_CURRENT_LIST_DIR}/indication_test.cpp)
target_link_libraries(indication_test PUBLIC GTest::gtest GTest::gtest_main indication)
gtest_discover_tests(indication_test TEST_PREFIX new:)
