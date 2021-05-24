include(GoogleTest)


# find_package(gtest REQUIRED)


add_executable(test_demo test_demo.cpp)
target_link_libraries(test_demo PUBLIC demo ${CONAN_LIBS_GTEST})
target_include_directories(test_demo PUBLIC ${CMAKE_CURRENT_LIST_DIR})
gtest_discover_tests(test_demo TEST_PREFIX new:)
