#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace ublas = boost::numeric::ublas;

using matrix = ublas::matrix<unsigned long long int>;

matrix matrix_power(matrix base, int exp) {
    if (base.size1() != base.size2()) {
        throw std::runtime_error("Matrix must be square");
    }

    matrix result(base.size1(), base.size2());
    for (size_t i = 0; i < result.size1(); ++i) {
        for (size_t j = 0; j < result.size2(); ++j) {
            result(i, j) = (i == j);
        }
    }

    while (exp > 0) {
        if (exp % 2 == 1) {
            result = ublas::prod(result, base);
        }
        base = ublas::prod(base, base);
        exp /= 2;
    }
    return result;
}

unsigned long long int fibonacci(int n) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    matrix F(2, 2);
    F(0, 0) = 1; F(0, 1) = 1;
    F(1, 0) = 1; F(1, 1) = 0;

    matrix Fn = matrix_power(F, n - 1);

    return Fn(0, 0);
}

int main() {
    int n = 90;
    unsigned long long int result = fibonacci(n);
    
    std::cout << "Fib(" << n << ") = " << result << std::endl;
}
