#include <algorithm>
#include <cassert>
#include <vector>

struct Rectangle {
    double x_left = 0, y_top = 0, x_right = 0, y_bottom = 0;
};

double cross_area(Rectangle a, Rectangle b) {
    double new_x_left = std::max(a.x_left, b.x_left);
    double new_x_right = std::min(a.x_right, b.x_right);
    double new_y_top = std::max(a.y_top, b.y_top);
    double new_y_bottom = std::min(a.y_bottom, b.y_bottom);

    if (new_x_left > new_x_right || new_y_top > new_y_bottom) {
        return 0;
    }

    return (new_x_right - new_x_left) * (new_y_bottom - new_y_top);
}

Rectangle min_common_coverage(std::vector<Rectangle> vector) {
    if (vector.empty()) return Rectangle{};

    double new_x_left = vector.at(0).x_left;
    double new_x_right = vector.at(0).x_right;
    double new_y_top = vector.at(0).y_top;
    double new_y_bottom = vector.at(0).y_bottom;

    for (auto rec : vector) {
        new_x_left = std::min(new_x_left, rec.x_left);
        new_x_right = std::max(new_x_right, rec.x_right);
        new_y_top = std::max(new_y_top, rec.y_top);
        new_y_bottom = std::min(new_y_bottom, rec.y_bottom);
    }

    return Rectangle{new_x_left, new_y_top, new_x_right, new_y_bottom};
}

int main() {
    Rectangle r1 = Rectangle{-1, 1, 1, -1};
    Rectangle r2 = Rectangle{-2, 2, 2, -2};

    std::vector<Rectangle> vec = std::vector<Rectangle>{r1, r2};

    assert(std::abs(cross_area(r1, r2) - 4) < 1e-6);

    auto cover = min_common_coverage(vec);

    assert(std::abs(cover.x_left + 2) < 1e-6);
    assert(std::abs(cover.x_right - 2) < 1e-6);
    assert(std::abs(cover.y_bottom - 2) < 1e-6);
    assert(std::abs(cover.y_top + 2) < 1e-6);
}
