cmake_minimum_required(VERSION 3.28)
project(homework_10_01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable benchmark tests" FORCE)
add_subdirectory(benchmark)

add_executable(vector_capacity vector_capacity.cpp)
target_link_libraries(vector_capacity PRIVATE benchmark)

add_executable(deque_memory deque_memory.cpp)
target_link_libraries(deque_memory PRIVATE benchmark)
