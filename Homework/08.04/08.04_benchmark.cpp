#include <benchmark/benchmark.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <string_view>
#include <limits>

constexpr std::string_view TARGET_PHRASE = "methinksitislikeaweasel";
constexpr std::string_view ALPHABET = "abcdefghijklmnopqrstuvwxyz";
constexpr size_t PHRASE_LENGTH = 23;
constexpr int COPIES_COUNT = 100;
constexpr double MUTATION_RATE = 0.05;

size_t calculate_fitness(std::string_view generated_string) {
    size_t differences = 0;
    for (size_t i = 0; i < PHRASE_LENGTH; ++i) {
        if (generated_string[i] != TARGET_PHRASE[i]) {
            differences++;
        }
    }
    return differences;
}

std::string generate_random_string(size_t length, std::default_random_engine& rng, std::uniform_int_distribution<>& char_dist) {
    std::string random_string;
    random_string.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        random_string += ALPHABET[char_dist(rng)];
    }
    return random_string;
}

static void BM_CalculateFitness(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<> char_dist(0, ALPHABET.length() - 1);
    std::string test_string = generate_random_string(PHRASE_LENGTH, rng, char_dist);
    for (auto _ : state) {
        benchmark::DoNotOptimize(calculate_fitness(test_string));
    }
}
BENCHMARK(BM_CalculateFitness);

static void BM_GenerateRandomString(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_int_distribution<> char_dist(0, ALPHABET.length() - 1);
    for (auto _ : state) {
        benchmark::DoNotOptimize(generate_random_string(PHRASE_LENGTH, rng, char_dist));
    }
}
BENCHMARK(BM_GenerateRandomString);

static void BM_GeneticAlgorithmStep(benchmark::State& state) {
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_real_distribution<> mutation_dist(0.0, 1.0);
    std::uniform_int_distribution<> char_dist(0, ALPHABET.length() - 1);
    std::string parent_string = generate_random_string(PHRASE_LENGTH, rng, char_dist);

    for (auto _ : state) {
        std::vector<std::string> children;
        children.reserve(COPIES_COUNT);

        for (int i = 0; i < COPIES_COUNT; ++i) {
            std::string child = parent_string;
            for (size_t j = 0; j < PHRASE_LENGTH; ++j) {
                if (mutation_dist(rng) < MUTATION_RATE) {
                    child[j] = ALPHABET[char_dist(rng)];
                }
            }
            children.push_back(child);
        }

        auto best_child_it = std::min_element(children.cbegin(), children.cend(),
            [](const std::string& a, const std::string& b) {
                return calculate_fitness(a) < calculate_fitness(b);
            });

        parent_string = *best_child_it;
        benchmark::DoNotOptimize(parent_string);
    }
}
BENCHMARK(BM_GeneticAlgorithmStep);

BENCHMARK_MAIN();
