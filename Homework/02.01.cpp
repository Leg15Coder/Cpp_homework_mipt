#include <numbers>
#include <cmath>
#include <iostream>

int main() {
    int n = 0;
    std::cin >> n;

    double const five_sqrt = std::sqrt(5);
    double const phi = (1 + std::sqrt(5)) / 2;
    double const neg_phi = 1 - phi;

    double fn = (std::pow(phi, n) - std::pow(neg_phi, -n)) / five_sqrt;

    std::cout << static_cast<int>(fn) << std::endl;
    return 0;
}
