find_package(GTest REQUIRED CONFIG)
include(GoogleTest)

add_executable(test_result test_result.cpp)
target_link_libraries(test_result
  PRIVATE
    ${CMAKE_PROJECT_NAME}
    GTest::gtest
    GTest::gtest_main
)

gtest_discover_tests(
    test_result
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    PROPERTIES
      FAIL_REGULAR_EXPRESSION "FAILED"
)

