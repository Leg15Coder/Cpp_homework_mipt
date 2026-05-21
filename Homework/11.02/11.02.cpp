#include <benchmark/benchmark.h>
#include <functional>
#include <memory>

[[gnu::noinline]] int free_function(int x) {
    return x + 1;
}

static void BM_FreeFunction(benchmark::State& state) {
    volatile int x = 1;
    for (auto _ : state) {
        benchmark::DoNotOptimize(free_function(x));
    }
}
BENCHMARK(BM_FreeFunction);

class TestClass {
public:
    [[gnu::noinline]] int member_function(int x) {
        return x + 1;
    }
};

static void BM_MemberFunction(benchmark::State& state) {
    TestClass instance;
    volatile int x = 1;
    for (auto _ : state) {
        benchmark::DoNotOptimize(instance.member_function(x));
    }
}
BENCHMARK(BM_MemberFunction);

class Base {
public:
    virtual int virtual_function(int x) [[gnu::noinline]] = 0;
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    int virtual_function(int x) override [[gnu::noinline]] {
        return x + 1;
    }
};

static void BM_VirtualFunction(benchmark::State& state) {
    std::unique_ptr<Base> instance = std::make_unique<Derived>();
    volatile int x = 1;
    for (auto _ : state) {
        benchmark::DoNotOptimize(instance->virtual_function(x));
    }
}
BENCHMARK(BM_VirtualFunction);

struct Functor {
    [[gnu::noinline]] int operator()(int x) const {
        return x + 1;
    }
};

static void BM_Functor(benchmark::State& state) {
    Functor functor;
    volatile int x = 1;
    for (auto _ : state) {
        benchmark::DoNotOptimize(functor(x));
    }
}
BENCHMARK(BM_Functor);

static void BM_AutoLambda(benchmark::State& state) {
    auto lambda = [](int x) {
        return x + 1;
    };
    volatile int x = 1;
    for (auto _ : state) {
        benchmark::DoNotOptimize(lambda(x));
    }
}
BENCHMARK(BM_AutoLambda);

static void BM_StdFunction(benchmark::State& state) {
    std::function<int(int)> func = [](int x) {
        return x + 1;
    };
    volatile int x = 1;
    for (auto _ : state) {
        benchmark::DoNotOptimize(func(x));
    }
}
BENCHMARK(BM_StdFunction);

BENCHMARK_MAIN();
