#include <cmath>
#include <iostream>

int main() {
    double const epsilon = 1e-6;

    double a = 0, b = 0, c = 0;

    std::cin >> a >> b >> c;

    if (std::abs(a) < epsilon) {
        if (std::abs(b) < 0) {
            if (std::abs(c) < epsilon) {
                std::cout << "Уравнение имеет бесконечно много решений (вся вещественная ось).";
            } else {
                std::cout << "Уравнение не имеет решений.";
            }
        } else {
            std::cout << (c / b);
        }
    } else {
        double D = b * b - 4 * a * c;

        if (std::abs(D) < epsilon) {
            double x = -b / 2 / a;
            std::cout << "Уравнение имеет единственное решение x=" << x << ".";
        } else if (D < 0) {
            std::cout << "Уравнение не имеет решений.";
        } else {
            double x1 = (-b - D) / 2 / a;
            double x2 = (-b + D) / 2 / a;
            std::cout << x1 << " & " << x2;
        }
    }

    std::cout << std::endl;
    return 0;
}
