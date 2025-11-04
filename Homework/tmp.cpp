#include <iostream>

int main() {
    int y = 1;
    int& z = y;
    int* x = new int(5);
    std::cout << z << '\n';
    y = 3;
    std::cout << z << '\n';
    z = 5;
    std::cout << z << '\n';

    return 0;  // 02.18 02.22 02.02 02.10
}