#include <numbers>
#include <cassert>
#include <cmath>

class Triangle {
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double area() const {
        return a * b * c;
    }

private:
    double a = 0, b = 0, c = 0;
};

class Square {
public:
    double a = 0;

    Square(double a) {
        this->a = a;
    }

    double area() {
        return a * a;
    }
};

class Circle {
public:
    double r = 0;

    Circle(double r) {
        this->r = r;
    }

    double area() {
        return r * r * std::numbers::pi;
    }
};

int main() {
    Triangle tri = Triangle(1, 1, std::sqrt(2));
    Square sq = Square(1);
    Circle circ = Circle(1);

    assert(std::abs(tri.area() - 0.5) < 1e-6);
    assert(std::abs(sq.area() - 1) < 1e-6);
    assert(std::abs(circ.area() - std::numbers::pi) < 1e-6);
}