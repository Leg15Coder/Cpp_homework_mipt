#include <numbers>
#include <cassert>
#include <cmath>
#include <vector>
#include <iostream>

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
};

class Triangle : public Shape {
public:
    Triangle(double a, double b, double c) : a(a), b(b), c(c) {}

    double area() const override final {
        double p = perimeter() / 2;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }

    double perimeter() const override final {
        return a + b + c;
    }

private:
    double a = 0, b = 0, c = 0;
};

class Square final : public Shape {
public:
    Square(double a) : a(a) {}

    double area() const override {
        return a * a;
    }

    double perimeter() const override {
        return 4 * a;
    }

private:
    double a = 0;
};

class Circle final : public Shape {
public:
    Circle(double r) : r(r) {}

    double area() const override {
        return r * r * std::numbers::pi;
    }

    double perimeter() const override {
        return 2 * std::numbers::pi * r;
    }

private:
    double r = 0;
};

int main() {
    Triangle tri = Triangle(1, 1, std::sqrt(2));
    Square sq = Square(1);
    Circle circ = Circle(1);

    assert(std::abs(tri.area() - 0.5) < 1e-6);
    assert(std::abs(sq.area() - 1) < 1e-6);
    assert(std::abs(circ.area() - std::numbers::pi) < 1e-6);

    std::vector<Shape*> shapes;
    
    shapes.push_back(new Triangle(3, 4, 5));
    shapes.push_back(new Square(2));
    shapes.push_back(new Circle(3));

    double totalArea = 0;
    double totalPerimeter = 0;
    
    for (const auto& shape : shapes) {
        totalArea += shape->area();
        totalPerimeter += shape->perimeter();
        
        std::cout << "Area: " << shape->area() 
                  << ", Perimeter: " << shape->perimeter() << std::endl;
    }
    
    std::cout << "Total area: " << totalArea << std::endl;
    std::cout << "Total perimeter: " << totalPerimeter << std::endl;

    for (auto shape : shapes) delete shape;
    shapes.clear();
}
