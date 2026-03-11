cmake_minimum_required(VERSION 3.10)
project(allocator_benchmark CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Boost
find_package(Boost 1.70 REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Find Google Benchmark
find_package(benchmark REQUIRED)

if (benchmark_FOUND)
    add_executable(09.09 09.09.cpp)
    target_link_libraries(09.09 PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
        ${Boost_LIBRARIES}
    )
    # Add compile options for benchmark to work correctly (e.g., -pthread)
    target_compile_options(09.09 PRIVATE -pthread)
    # Target include directory for the source file itself
    target_include_directories(09.09 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
else()
    message(FATAL_ERROR "Google Benchmark not found!")
endif()