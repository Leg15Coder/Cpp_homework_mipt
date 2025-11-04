#include <any>
#include <cassert>
#include <string>
#include <vector>
#include <iostream>

struct Point {
    double x, y;
};

class Shape {
public:
    Shape(double a, double b) : m_a(a), m_b(b) {}

    virtual ~Shape() = default;
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
protected:
    std::vector<Point> points;
    double m_a = 0, m_b = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double a, double b) : Shape(a, b) {}

    double perimeter() const override final {
        return (m_a + m_b) * 2;
    }

    double area() const override final {
        return m_a * m_b;
    }
};

class Square : public Rectangle {
public:
    Square(double a) : Rectangle(a, a) {}
};

int main() {
    std::vector<Shape*> shapes;
    shapes.push_back(new Rectangle(1, 2));
    shapes.push_back(new Square(5));

    for (auto shape : shapes) {
        std::cout << "Area: " << shape->area() << '\t';
        std::cout << "Perimeter: " << shape->perimeter() << '\n';
        delete shape;
    }
}
