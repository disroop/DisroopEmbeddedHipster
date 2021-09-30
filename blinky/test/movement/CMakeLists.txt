add_subdirectory(internal)

add_executable(movement_test
        ${CMAKE_CURRENT_LIST_DIR}/movement_test.cpp)
target_link_libraries(movement_test PUBLIC GTest::gtest GTest::gtest_main movement)
gtest_discover_tests(movement_test TEST_PREFIX new:)