cmake_minimum_required(VERSION 3.14)
project(Homework14_03)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Google Benchmark
set(benchmark_DIR /home/ryazhskikh_dima_76/Cpp_homework_mipt/Homework/10.01/build/benchmark)
find_package(benchmark REQUIRED)

add_executable(scalability_bench benchmark.cpp)
target_link_libraries(scalability_bench PRIVATE benchmark::benchmark pthread)
