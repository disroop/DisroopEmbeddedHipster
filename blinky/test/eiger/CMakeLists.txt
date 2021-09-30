add_executable(timer_test
        ${CMAKE_CURRENT_LIST_DIR}/timer_test.cpp
        ${CMAKE_CURRENT_LIST_DIR}/fake_delay.cpp
        ${CMAKE_CURRENT_LIST_DIR}/fake_delay.hpp
        ${CMAKE_CURRENT_LIST_DIR}/scheduler_test.cpp)
target_link_libraries(timer_test PUBLIC GTest::gtest GTest::gtest_main absl::base eiger)
gtest_discover_tests(timer_test TEST_PREFIX new:)