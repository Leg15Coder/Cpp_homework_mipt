cmake_minimum_required(VERSION 3.14)
project(homework_11_02 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHMARK_ENABLE_TESTING OFF)

include(FetchContent)
FetchContent_Declare(
  google_benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        v1.8.0
)

FetchContent_GetProperties(google_benchmark)
if(NOT google_benchmark_POPULATED)
  FetchContent_Populate(google_benchmark)
  add_subdirectory(${google_benchmark_SOURCE_DIR} ${google_benchmark_BINARY_DIR})
endif()

add_executable(11.02 11.02.cpp)
target_link_libraries(11.02 PRIVATE benchmark::benchmark)
