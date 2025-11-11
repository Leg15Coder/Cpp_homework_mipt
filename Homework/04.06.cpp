#include <array>
#include <cmath>


template<int n>
consteval long factorial() {
    static_assert(n >= 0);
    return factorial<n - 1>() * n;
}


template<>
consteval long factorial<0>() {
    return 1L;
}


template<double eps, double x, int n>
consteval double exp() {
    constexpr double elem = std::pow(x, n) / static_cast<double>(factorial<n>());

    if constexpr (elem >= eps) return exp<eps, x, n + 1>() + elem;
    else return elem;
}


template<double eps, double x>
consteval double exp() {
    return exp<eps, x, 0>();
}


template<double eps>
consteval double exp() {
    return exp<eps, 1.0>();
}


int main() {
    constexpr std::array<double, 7> accuracy = {1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6};

    static_assert(std::abs(std::exp(1.0) - exp<accuracy[0]>()) < accuracy[0]);
    static_assert(std::abs(std::exp(1.0) - exp<accuracy[1]>()) < accuracy[1]);
    static_assert(std::abs(std::exp(1.0) - exp<accuracy[2]>()) < accuracy[2]);
    static_assert(std::abs(std::exp(1.0) - exp<accuracy[3]>()) < accuracy[3]);
    static_assert(std::abs(std::exp(1.0) - exp<accuracy[4]>()) < accuracy[4]);
    static_assert(std::abs(std::exp(1.0) - exp<accuracy[5]>()) < accuracy[5]);
    static_assert(std::abs(std::exp(1.0) - exp<accuracy[6]>()) < accuracy[6]);
}