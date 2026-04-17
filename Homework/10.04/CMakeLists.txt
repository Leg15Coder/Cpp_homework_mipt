cmake_minimum_required(VERSION 3.10)
project(homework_10_04)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(boost_1_85_0)
add_executable(fib_matrix 10.04.cpp)
