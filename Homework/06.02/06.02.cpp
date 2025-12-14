import rational;

import <cassert>;
import <cmath>;
import <sstream>;
import <vector>;


using numbers::Rational;


bool equal(double x, double y, double eps = 1e-6) {
    return std::abs(x - y) < eps;
}

int main()
{
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
}
