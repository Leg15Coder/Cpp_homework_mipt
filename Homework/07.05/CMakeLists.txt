cmake_minimum_required(VERSION 3.14)
project(HybridSortBenchmark)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Google Benchmark
FetchContent_Declare(
  benchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.8.0.zip
)
FetchContent_MakeAvailable(benchmark)

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

# Benchmark
add_executable(
  benchmarks
  benchmark.cpp
)
target_link_libraries(
  benchmarks
  benchmark::benchmark_main
)
