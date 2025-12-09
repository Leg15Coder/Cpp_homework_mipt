#include <iostream>
#include <optional>
#include <variant>
#include <cmath>
#include <utility>
#include <numeric>

using RootsVariant = std::variant<double, std::pair<double, double>, std::monostate>;

std::optional<RootsVariant> solve(double a, double b, double c) {
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                return std::make_optional(std::monostate{});
            } else {
                return std::nullopt;
            }
        } else {
            return std::make_optional(RootsVariant(-c / b));
        }
    } else {
        double discriminant = b * b - 4 * a * c;

        if (discriminant > 0) {
            double x1 = (-b + std::sqrt(discriminant)) / (2 * a);
            double x2 = (-b - std::sqrt(discriminant)) / (2 * a);
            return std::make_optional(RootsVariant(std::make_pair(x1, x2)));
        } else if (discriminant == 0) {
            double x = -b / (2 * a);
            return std::make_optional(RootsVariant(x));
        } else {
            return std::nullopt;
        }
    }
}

int main() {
    double a, b, c;
    std::cout << "Enter coefficients a, b, and c for ax^2 + bx + c = 0:\n";
    std::cout << "a: ";
    std::cin >> a;
    std::cout << "b: ";
    std::cin >> b;
    std::cout << "c: ";
    std::cin >> c;

    std::optional<RootsVariant> result = solve(a, b, c);

    if (!result.has_value()) {
        std::cout << "No real solutions found.\n";
    } else {
        const RootsVariant& roots = result.value();
        if (std::holds_alternative<double>(roots)) {
            std::cout << "One real solution: x = " << std::get<double>(roots) << "\n";
        } else if (std::holds_alternative<std::pair<double, double>>(roots)) {
            std::pair<double, double> two_roots = std::get<std::pair<double, double>>(roots);
            std::cout << "Two real solutions: x1 = " << two_roots.first << ", x2 = " << two_roots.second << "\n";
        } else if (std::holds_alternative<std::monostate>(roots)) {
            std::cout << "Infinite number of solutions.\n";
        }
    }
}
