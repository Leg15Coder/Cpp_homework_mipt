#include <iostream>
#include <iterator>
#include <limits>

class FibonacciIterator {
public:
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = const int*;
    using reference = const int&;
    using iterator_category = std::forward_iterator_tag;

    FibonacciIterator() : m_current_fib(0), m_next_fib(0) {}

    FibonacciIterator(int current, int next) : m_current_fib(current), m_next_fib(next) {}

    FibonacciIterator& operator++() {
        int temp = m_current_fib;
        m_current_fib = m_next_fib;

        if (m_next_fib > std::numeric_limits<int>::max() - temp) {
            m_next_fib = std::numeric_limits<int>::max();
        } else {
            m_next_fib += temp;
        }
        return *this;
    }

    FibonacciIterator operator++(int) {
        FibonacciIterator temp = *this;
        ++(*this);
        return temp;
    }

    reference operator*() const {
        return m_current_fib;
    }

    friend bool operator==(const FibonacciIterator& a, const FibonacciIterator& b) {
        return a.m_current_fib == b.m_current_fib && a.m_next_fib == b.m_next_fib;
    }

    friend bool operator!=(const FibonacciIterator& a, const FibonacciIterator& b) {
        return !(a == b);
    }

private:
    int m_current_fib;
    int m_next_fib;
};

class FibonacciSequence {
public:
    explicit FibonacciSequence(int limit) : m_limit(limit) {}

    FibonacciIterator begin() const {
        return FibonacciIterator(0, 1);
    }

    FibonacciIterator end() const {
        return FibonacciIterator(m_limit, std::numeric_limits<int>::max());
    }

private:
    int m_limit;
};


int main() {
    std::cout << "Fibonacci sequence up to 1000: ";
    FibonacciSequence fib_seq(1000);
    for (FibonacciIterator it = fib_seq.begin(); *it < 1000; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
