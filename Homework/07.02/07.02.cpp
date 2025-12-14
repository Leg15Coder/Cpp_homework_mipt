import rational;

import <cassert>;
import <iostream>;
import <string>;
import <optional>;
import <variant>;
import <cmath>;
import <sstream>;
import <stdexcept>;
import <vector>;


using numbers::Rational;

bool equal(double x, double y, double eps = 1e-6) {
    return std::abs(x - y) < eps;
}

void demonstrate_vector_exceptions() {
    try {
        std::vector<int> v;
        v.reserve(2'000'000'000);  // std::bad_alloc выбрасывается, когда оператор new не может выделить запрошенный объем памяти.
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    try {
        std::vector<int> v;
        v.resize(v.max_size() + 1); // создается объект, размер которого превышает максимально допустимый. (std::length_error)
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    try {
        std::vector<int> v = {1};
        v.at(2); // std::out_of_range так как происходит обращение к элементу за границами массива
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    try {
        std::optional<int> opt;
        opt.value();  // попытка взять значение у nullopt (std::bad_optional_access)
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    try {
        std::variant<int, std::string> v;
        v = 123;
        std::get<std::string>(v); // std::bad_variant_access - попытка взять тип варианта, но при этом вариант в данный момент хранит другой тип 
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    Rational x = 1, y(2, 1);

	std::vector < int > vector_2(5);

	std::vector < int > vector_3 = { 1, 2, 3, 4, 5 };

	assert(equal(static_cast < double > (x), 1));

	assert((x += y) == Rational(+3, 1));

	assert((x -= y) == Rational(+1, 1));

	assert((x *= y) == Rational(+2, 1));

	assert((x /= y) == Rational(+1, 1));

	assert((x ++  ) == Rational(+1, 1));

	assert((x --  ) == Rational(+2, 1));

	assert((  ++ y) == Rational(+3, 1));

	assert((  -- y) == Rational(+2, 1));

	[[maybe_unused]] auto z = 0;

	assert((x +  y) == Rational(+3, 1));

	assert((x -  y) == Rational(-1, 1));

	assert((x *  y) == Rational(+2, 1));

	assert((x /  y) == Rational(+1, 2));

	assert((x += 1) == Rational(+2, 1));

	assert((x +  1) == Rational(+3, 1));

	assert((1 +  y) == Rational(+3, 1));

	assert((1 +  1) == Rational(+2, 1));

	assert((x <  y) == 0);

	assert((x >  y) == 0);

	assert((x <= y) == 1);

	assert((x >= y) == 1);

	assert((x == y) == 1);

	assert((x != y) == 0);

	std::stringstream stream_1("1/2");

	std::stringstream stream_2;

	stream_1 >> x;

	stream_2 << x;

	assert(stream_2.str() == stream_1.str());

    try {
        Rational r(1, 0);
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    try {
        demonstrate_vector_exceptions();
    } catch (const std::exception& e) {
        std::cerr << "Caught an unexpected std::exception in main: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Caught an unknown exception in main." << std::endl;
    }
}
