#include <iostream>
#include <format>

int main() {
    double const x = 1.0;
    int n = 0;
    long long factorial = 1;
    double eps = 0, e = 0, elem = 0;
    std::cin >> eps;

    do {
        elem = x / static_cast<double>(factorial);
        e += elem;
        n++;
        factorial *= n > 0 ? n : 1;
    } while (elem > eps);

    std::cout << std::format("{:.{}f}", e, 10) << std::endl;
}