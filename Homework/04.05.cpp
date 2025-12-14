#include <cassert>
#include <limits>


template<int N>
struct Fibonacci {
    static_assert(N >= 0);
    
    static constexpr int prev = Fibonacci<N - 1>::value;
    static constexpr int before_prev = Fibonacci<N - 2>::value;

    static_assert(prev <= std::numeric_limits<int>::max() - before_prev);
    
    static constexpr int value = prev + before_prev;
};


template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};


template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};


template<int N>
constexpr int Fibonacci_v = Fibonacci<N>::value;


int main() {
    static_assert(Fibonacci_v<0> == 0);
    static_assert(Fibonacci_v<1> == 1);
    static_assert(Fibonacci_v<2> == 1);
    static_assert(Fibonacci_v<3> == 2);
    static_assert(Fibonacci_v<4> == 3);
    static_assert(Fibonacci_v<5> == 5);
    static_assert(Fibonacci_v<6> == 8);
    static_assert(Fibonacci_v<7> == 13);
}
