#include <benchmark/benchmark.h>
#include <iostream>

class Entity_v1 {
public:
    Entity_v1(int value) : private_field(value) {}

    void print() const {
        // std::cout << "Entity_v1::private_field = " << private_field << std::endl;
    }

private:
    int private_field;
};

class Entity_v2 {
public:
    int public_field;
};

class Entity_v3 {
public:
    Entity_v3(int value) : private_data(value) {}

    void print() const {
        // std::cout << "Entity_v3::private_data = " << private_data << std::endl;
    }

private:
    int private_data;
};

static void BM_reinterpret_cast_class(benchmark::State& state) {
    Entity_v1 entity1(1);
    for (auto _ : state) {
        Entity_v2& entity2 = reinterpret_cast<Entity_v2&>(entity1);
        entity2.public_field = 2;
        benchmark::DoNotOptimize(entity1);
    }
}
BENCHMARK(BM_reinterpret_cast_class);

static void BM_reinterpret_cast_pointer(benchmark::State& state) {
    Entity_v3 simple_entity(3);
    for (auto _ : state) {
        int* fraudulent_ptr = reinterpret_cast<int*>(&simple_entity);
        *fraudulent_ptr = 4;
        benchmark::DoNotOptimize(simple_entity);
    }
}
BENCHMARK(BM_reinterpret_cast_pointer);

class Entity_public {
public:
    Entity_public(int value) : public_field(value) {}
    int public_field;
};

static void BM_direct_access(benchmark::State& state) {
    Entity_public entity(1);
    for (auto _ : state) {
        entity.public_field = 2;
        benchmark::DoNotOptimize(entity);
    }
}
BENCHMARK(BM_direct_access);

class Entity_setter {
public:
    Entity_setter(int value) : private_field(value) {}
    void setValue(int value) { private_field = value; }
private:
    int private_field;
};

static void BM_setter_access(benchmark::State& state) {
    Entity_setter entity(1);
    for (auto _ : state) {
        entity.setValue(2);
        benchmark::DoNotOptimize(entity);
    }
}
BENCHMARK(BM_setter_access);

BENCHMARK_MAIN();
