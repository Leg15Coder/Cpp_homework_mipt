#include <cassert>
#include <cmath>
#include <stdexcept>
#include <limits>

int log2_int(int n) {
    if (n <= 0) {
        throw std::domain_error("Logarithm of non-positive number is undefined");
    }
    unsigned int u_n = static_cast<unsigned int>(n);
    int result = -1;
    while (u_n > 0) {
        u_n >>= 1;
        result++;
    }
    return result;
}

union FloatUnion {
    float f;
    unsigned int i;
};

int log2_float(float n) {
    if (n <= 0.0f) {
        throw std::domain_error("Logarithm of non-positive number is undefined");
    }

    FloatUnion u;
    u.f = n;
    unsigned int i_n = u.i;

    unsigned int exponent = (i_n >> 23) & 0xFF;
    unsigned int mantissa = i_n & 0x7FFFFF;

    if (exponent == 0xFF) {
        throw std::domain_error("Logarithm of infinity or NaN is undefined");
    }

    if (exponent == 0) {
        if (mantissa == 0) {
            throw std::domain_error("Logarithm of zero is undefined");
        }
        return log2_int(mantissa) - 149;
    }

    return exponent - 127;
}

int main() {
    assert(log2_int(1) == 0);
    assert(log2_int(2) == 1);
    assert(log2_int(3) == 1);
    assert(log2_int(4) == 2);
    assert(log2_int(1023) == 9);
    assert(log2_int(1024) == 10);
    assert(log2_int(1025) == 10);
    assert(log2_int(2147483647) == 30);

    assert(log2_float(1.0f) == 0);
    assert(log2_float(2.0f) == 1);
    assert(log2_float(3.0f) == 1);
    assert(log2_float(3.5f) == 1);
    assert(log2_float(4.0f) == 2);
    assert(log2_float(1023.0f) == 9);
    assert(log2_float(1024.0f) == 10);
    assert(log2_float(1025.0f) == 10);
    
    FloatUnion fu_denorm;
    fu_denorm.i = 0x00400000;
    assert(log2_float(fu_denorm.f) == -127);

    FloatUnion fu_denorm2;
    fu_denorm2.i = 0x00000001;
    assert(log2_float(fu_denorm2.f) == -149);

    try {
        log2_int(0);
        assert(false);
    } catch (const std::domain_error& e) {
        // Expected
    }

    try {
        log2_int(-10);
        assert(false);
    } catch (const std::domain_error& e) {
        // Expected
    }

    try {
        log2_float(0.0f);
        assert(false);
    } catch (const std::domain_error& e) {
        // Expected
    }

    try {
        log2_float(-5.0f);
        assert(false);
    } catch (const std::domain_error& e) {
        // Expected
    }

    try {
        float inf = std::numeric_limits<float>::infinity();
        log2_float(inf);
        assert(false);
    } catch (const std::domain_error& e) {
        // Expected
    }

    try {
        float nan = std::numeric_limits<float>::quiet_NaN();
        log2_float(nan);
        assert(false);
    } catch (const std::domain_error& e) {
        // Expected
    }
}
