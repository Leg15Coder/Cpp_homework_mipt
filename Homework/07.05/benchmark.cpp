#include <benchmark/benchmark.h>
#include "sort.hpp"
#include <vector>
#include <algorithm>
#include <numeric>

static void BM_HybridSort(benchmark::State& state) {
  std::vector<double> vec(100000);
  std::iota(vec.rbegin(), vec.rend(), 0.0);

  long threshold = state.range(0);

  for (auto _ : state) {
    state.PauseTiming();
    std::vector<double> temp_vec = vec;
    state.ResumeTiming();
    sort(temp_vec, threshold);
  }
}
BENCHMARK(BM_HybridSort)->DenseRange(0, 128, 16);

BENCHMARK_MAIN();