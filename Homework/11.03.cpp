#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <algorithm>
#include <string>

template <typename T>
void print_container(const T& container) {
    std::cout << ": [ ";
    for (const auto& item : container) {
        std::cout << item << " ";
    }
    std::cout << "]\n";
}

template <typename RandomAccessIterator, typename Comparator>
void insertion_sort(RandomAccessIterator first, RandomAccessIterator last, Comparator comp) {
    if (first == last) return;
    for (auto i = std::next(first); i != last; ++i) {
        auto key = std::move(*i);
        auto j = i;
        while (j != first && comp(key, *std::prev(j))) {
            *j = std::move(*std::prev(j));
            --j;
        }
        *j = std::move(key);
    }
}

template <typename RandomAccessIterator, typename ValueType, typename Comparator>
RandomAccessIterator partition(RandomAccessIterator first, RandomAccessIterator last, const ValueType& pivot, Comparator comp) {
    auto i = first;
    for (auto j = first; j != last; ++j) {
        if (comp(*j, pivot)) {
            std::iter_swap(i++, j);
        }
    }
    return i;
}

template <typename T, typename Comparator>
const T& choose_pivot(const T& a, const T& b, const T& c, Comparator comp) {
    if (comp(a, b)) {
        if (comp(b, c)) return b;
        if (comp(a, c)) return c;
        return a;
    }

    if (comp(a, c)) return a;
    if (comp(b, c)) return c;
    return b;
}

template <typename RandomAccessIterator, typename Comparator>
void quick_sort_impl(RandomAccessIterator first, RandomAccessIterator last, Comparator comp) {
    auto const size = std::distance(first, last);
    if (size > 16) {
        auto middle_it = first + size / 2;
        const auto& pivot = choose_pivot(*first, *middle_it, *std::prev(last), comp);

        auto partition_point = partition(first, last, pivot, comp);
        
        quick_sort_impl(first, partition_point, comp);
        quick_sort_impl(partition_point, last, comp);
    } else if (size > 1) {
        insertion_sort(first, last, comp);
    }
}


template <typename RandomAccessIterator, typename Comparator>
void custom_sort(RandomAccessIterator first, RandomAccessIterator last, Comparator comp) {
    quick_sort_impl(first, last, comp);
}

template <typename RandomAccessIterator>
void custom_sort(RandomAccessIterator first, RandomAccessIterator last) {
    using ValueType = typename std::iterator_traits<RandomAccessIterator>::value_type;
    quick_sort_impl(first, last, std::less<ValueType>());
}


bool descending_order(int a, int b) {
    return a > b;
}

int main() {
    std::vector<int> original_vec = {73, 17, 51, 6, 74, 94, 43, 48, 91, 56};
    print_container(original_vec);
    std::cout << "\n";

    auto vec1 = original_vec;
    custom_sort(vec1.begin(), vec1.end(), descending_order);
    print_container(vec1);
    std::cout << "\n";

    auto vec2 = original_vec;
    custom_sort(vec2.begin(), vec2.end());
    print_container(vec2);
    std::cout << "\n";

    auto vec3 = original_vec;
    auto compare_by_last_digit = [](int a, int b) {
        return (a % 10) < (b % 10);
    };
    custom_sort(vec3.begin(), vec3.end(), compare_by_last_digit);
    print_container(vec3);
    std::cout << "\n";
}
