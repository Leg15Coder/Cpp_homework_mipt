cmake_minimum_required(VERSION 3.14)
project(HybridSortTest)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tests
enable_testing()

add_executable(
  tests
  test.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
