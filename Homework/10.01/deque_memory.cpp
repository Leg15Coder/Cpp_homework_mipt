#include <benchmark/benchmark.h>
#include <iostream>
#include <deque>
#include <iomanip>

static void BM_DequeMemory(benchmark::State& state) {
    for (auto _ : state) {
        std::deque<int> d;
        std::cout << "Index, Address" << std::endl;
        for (int i = 0; i < 256; ++i) {
            d.push_back(i);
            std::cout << std::setw(5) << i << ", " << &d.back() << std::endl;
        }

        // Calculate elements per block
        if (d.size() > 1) {
            for (size_t i = 1; i < d.size(); ++i) {
                if (reinterpret_cast<const char*>(&d[i]) - reinterpret_cast<const char*>(&d[i-1]) != sizeof(int)) {
                    std::cout << "Page Break" << std::endl;
                    size_t elements_per_block = i;
                    size_t block_size_bytes = elements_per_block * sizeof(int);
                    std::cout << "Elements per block: " << elements_per_block << std::endl;
                    std::cout << "Page size (bytes): " << block_size_bytes << std::endl;
                    break;
                }
            }
        }
    }
}
BENCHMARK(BM_DequeMemory);

BENCHMARK_MAIN();
