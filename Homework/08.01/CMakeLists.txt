cmake_minimum_required(VERSION 3.10)
project(homework_08_01_benchmark CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(../10.01/benchmark ${CMAKE_CURRENT_BINARY_DIR}/benchmark_build)
add_executable(benchmark_08_01 08.01_benchmark.cpp)

target_link_libraries(benchmark_08_01 PRIVATE benchmark::benchmark)
