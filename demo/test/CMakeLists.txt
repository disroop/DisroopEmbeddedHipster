include(GoogleTest)


find_package(GTest REQUIRED)


add_executable(test_demo test_demo.cpp)
target_link_libraries(test_demo PUBLIC demo GTest::gtest GTest::gtest_main)
gtest_discover_tests(test_demo TEST_PREFIX new:)
