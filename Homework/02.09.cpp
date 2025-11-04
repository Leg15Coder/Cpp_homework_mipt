#include <cassert>
#include <numeric>

int gcd(int a, int b) {
    if (a == b) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    assert(gcd(20, 30) == std::gcd(20, 30));
    assert(lcm(5, 7) == std::lcm(5, 7));
    return 0;
}
