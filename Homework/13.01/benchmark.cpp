#include "hex_converter.hpp"
#include <benchmark/benchmark.h>
#include <vector>
#include <string>
#include <cstdint>

static const std::vector<std::uint8_t> test_vector(1024, 0xAB);
static const std::string test_hex_string = to_hex_string(test_vector);


static void BM_ToHexString(benchmark::State& state) {
  for (auto _ : state) {
    std::string result = to_hex_string(test_vector);
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_ToHexString);

static void BM_FromHexString(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::uint8_t> result = from_hex_string(test_hex_string);
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_FromHexString);

BENCHMARK_MAIN();
