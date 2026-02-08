#include "gtest/gtest.h"
#include "sort.hpp"
#include <vector>
#include <algorithm>
#include <random>

TEST(HybridSortTest, EmptyVector) {
    std::vector<int> vec;
    sort(vec);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(HybridSortTest, AlreadySorted) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    sort(vec);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(HybridSortTest, ReverseSorted) {
    std::vector<int> vec = {6, 5, 4, 3, 2, 1};
    sort(vec);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(HybridSortTest, Duplicates) {
    std::vector<int> vec = {5, 2, 3, 2, 5, 1};
    sort(vec);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(HybridSortTest, RandomElements) {
    std::vector<int> vec(1000);
    std::iota(vec.begin(), vec.end(), 0);
    std::mt19937 g(std::random_device{}());
    std::shuffle(vec.begin(), vec.end(), g);

    sort(vec);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(HybridSortTest, SingleElement) {
    std::vector<int> vec = {42};
    sort(vec);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(HybridSortTest, LongVector) {
	std::vector<long> vec(1000);
	std::iota(vec.begin(), vec.end(), 0);
    std::mt19937 g(std::random_device{}());
    std::shuffle(vec.begin(), vec.end(), g);

    sort(vec);
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}