cmake_minimum_required(VERSION 3.10)
project(homework_10_02 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(10_16_min 10.16.cpp)
target_compile_options(10_16_min PRIVATE -Wall -Wextra -Wpedantic)

add_executable(10_17_min 10.17.cpp)
target_compile_options(10_17_min PRIVATE -Wall -Wextra -Wpedantic)
