#include <charconv>
#include <cmath>
#include <iostream>
#include <cassert>
#include "json.hpp"
#include <string>
#include <string_view>
#include <benchmark/benchmark.h>

float extract_nlohmann(std::string_view sv) {
    return nlohmann::json::parse(sv).get<float>();
}

float extract_from_chars(std::string_view sv) {
    float val = 0.0f;
    std::from_chars(sv.data(), sv.data() + sv.size(), val);
    return val;
}

float fast_float_parser(std::string_view sv) {
    const char* p = sv.data();
    const char* end = p + sv.size();
    
    float sign = 1.0f;
    if (p != end && *p == '-') {
        sign = -1.0f;
        ++p;
    }

    long long int_part = 0;
    while (p != end && *p >= '0' && *p <= '9') {
        int_part = int_part * 10 + (*p - '0');
        ++p;
    }

    float val = static_cast<float>(int_part);

    if (p != end && *p == '.') {
        ++p;
        long long frac_part = 0;
        long long divisor = 1;
        while (p != end && *p >= '0' && *p <= '9') {
            frac_part = frac_part * 10 + (*p - '0');
            divisor *= 10;
            ++p;
        }
        val += static_cast<float>(frac_part) / static_cast<float>(divisor);
    }

    return val * sign;
}

void test_parsers() {
    std::string_view s1 = "1234.5678";
    assert(std::abs(fast_float_parser(s1) - 1234.5678f) < 1e-4);
    assert(std::abs(extract_from_chars(s1) - 1234.5678f) < 1e-4);
    assert(std::abs(extract_nlohmann(s1) - 1234.5678f) < 1e-4);

    std::string_view s2 = "-0.001";
    assert(std::abs(fast_float_parser(s2) - (-0.001f)) < 1e-6);
    
    std::string_view s3 = "42";
    assert(std::abs(fast_float_parser(s3) - 42.0f) < 1e-6);
    
    std::cout << "All tests passed!" << std::endl;
}

static void BM_Nlohmann(benchmark::State& state) {
    std::string_view json_num = "1234.5678";
    for (auto _ : state) {
        benchmark::DoNotOptimize(extract_nlohmann(json_num));
    }
}
BENCHMARK(BM_Nlohmann);

static void BM_FromChars(benchmark::State& state) {
    std::string_view json_num = "1234.5678";
    for (auto _ : state) {
        benchmark::DoNotOptimize(extract_from_chars(json_num));
    }
}
BENCHMARK(BM_FromChars);

static void BM_FastParser(benchmark::State& state) {
    std::string_view json_num = "1234.5678";
    for (auto _ : state) {
        benchmark::DoNotOptimize(fast_float_parser(json_num));
    }
}
BENCHMARK(BM_FastParser);

int main(int argc, char** argv) {
    test_parsers();
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}
