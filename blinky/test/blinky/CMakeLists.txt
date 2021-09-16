add_subdirectory(mocks)
add_executable(blinky_test ${CMAKE_CURRENT_LIST_DIR}/blinky_test.cpp)

target_link_libraries(blinky_test PRIVATE GTest::gtest GTest::gtest_main blinky eiger indication_fake movement_fake)
gtest_discover_tests(blinky_test TEST_PREFIX new:)
