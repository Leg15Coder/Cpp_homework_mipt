cmake_minimum_required(VERSION 3.14)
project(FloatExtractionBenchmark)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(benchmark_DIR /home/ryazhskikh_dima_76/Cpp_homework_mipt/Homework/13.01/build/benchmark)
find_package(benchmark REQUIRED)

add_executable(float_bench main.cpp)

target_link_libraries(float_bench PRIVATE 
    benchmark::benchmark 
    pthread
)

target_include_directories(float_bench PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
