#include <algorithm>
#include <cassert>
#include <functional>
#include <future>
#include <iterator>
#include <numeric>
#include <ranges>
#include <thread>
#include <utility>
#include <vector>
#include <cmath>
#include <benchmark/benchmark.h>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////

struct ComplexTask {
    template <std::ranges::view V>
    auto operator()(V view) const {
        double result = 0.0;
        for (double x : view) {
            result += std::sin(x) * std::cos(x) + std::sqrt(std::abs(x));
        }
        return result;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
auto reduce_parallel(std::ranges::view auto view, T sum, unsigned int num_threads) {
    auto begin = std::begin(view), end = std::end(view);
    auto size = std::distance(begin, end);

    if (size > 0 && num_threads > 1) {
        unsigned int actual_threads = std::min(num_threads, static_cast<unsigned int>(size));
        
        std::vector<std::future<T>> futures;
        std::vector<std::jthread> threads;
        futures.reserve(actual_threads - 1);
        threads.reserve(actual_threads - 1);

        auto step = size / actual_threads;

        for (unsigned int i = 0; i < actual_threads - 1; ++i) {
            auto range = std::ranges::subrange(begin, std::next(begin, step));
            
            std::packaged_task<T(decltype(range))> task{ComplexTask{}};
            futures.push_back(task.get_future());
            threads.emplace_back(std::move(task), range);
            
            std::advance(begin, step);
        }

        auto range = std::ranges::subrange(begin, end);
        sum += ComplexTask{}(range);

        for (auto& future : futures) {
            sum += future.get();
        }
    } else if (size > 0) {
        sum += ComplexTask{}(view);
    }

    return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////

static std::vector<double> data_vector;

static void Setup(const benchmark::State& state) {
    if (data_vector.empty()) {
        data_vector.resize(1 << 20);
        std::iota(data_vector.begin(), data_vector.end(), 1.0);
    }
}

static void BM_ReduceParallel(benchmark::State& state) {
    unsigned int num_threads = static_cast<unsigned int>(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(reduce_parallel(std::views::all(data_vector), 0.0, num_threads));
    }
}

BENCHMARK(BM_ReduceParallel)
    ->Arg(1)
    ->Arg(2)
    ->Arg(4)
    ->Arg(8)
    ->Arg(16)
    ->Unit(benchmark::kMillisecond)
    ->Setup(Setup);

BENCHMARK_MAIN();
