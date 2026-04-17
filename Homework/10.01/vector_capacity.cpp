#include <benchmark/benchmark.h>
#include <iostream>
#include <vector>

static void BM_VectorCapacity(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v;
        size_t last_capacity = 0;
        std::cout << "Size, Capacity" << std::endl;
        for (int i = 0; i < 1024; ++i) {
            v.push_back(i);
            if (v.capacity() != last_capacity) {
                last_capacity = v.capacity();
                std::cout << v.size() << ", " << last_capacity << std::endl;
            }
        }
    }
}
BENCHMARK(BM_VectorCapacity);

BENCHMARK_MAIN();
