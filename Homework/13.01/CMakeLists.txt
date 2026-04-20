# This project is managed by the top-level CMakeLists.txt

# Create the library with conversion functions
add_library(hex_converter_lib STATIC hex_converter.cpp)
target_include_directories(hex_converter_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Create the main executable
add_executable(hex_converter_1301 main.cpp)
target_link_libraries(hex_converter_1301 PRIVATE hex_converter_lib)

# Create the benchmark executable
add_executable(benchmark_runner_1301 benchmark.cpp)
target_link_libraries(benchmark_runner_1301 PRIVATE hex_converter_lib benchmark::benchmark)
