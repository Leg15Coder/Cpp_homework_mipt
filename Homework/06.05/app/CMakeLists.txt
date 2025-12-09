cmake_minimum_required(VERSION 3.10)
project(main_app)

add_executable(main_app main.cpp)

target_link_libraries(main_app PRIVATE dl)
