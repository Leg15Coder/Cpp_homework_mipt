#include <cmath>
#include <iostream>

int main() {
    double array[1024]{1, 2, 3, 4, 5};
    std::size_t size = 5;
    double min = array[0];
    double max = array[0];
    double sum = array[0];

    for (std::size_t i = 1; i < size; i++) {
        min = std::min(min, array[i]);
        min = std::max(max, array[i]);
        sum += array[i];
    }

    double avg = sum / static_cast<double>(size);
    double s = 0;

    for (std::size_t i = 0; i < size; i++) {
        s += std::pow(array[i] - avg, 2);
    }
    s /= static_cast<double>(size);
    s = std::sqrt(s);

    std::cout << min << " " << max << " " << sum << " " << avg << " " << s << '\n';
}