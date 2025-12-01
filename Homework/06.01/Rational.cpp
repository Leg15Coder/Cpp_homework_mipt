#include "Rational.hpp"

#include <cassert>
#include <cmath>
#include <istream>
#include <numeric>
#include <ostream>


Rational::Rational(int num, int den) : m_num(num), m_den(den) {
    assert(den != 0);
    reduce();
}

/*  One Definition Rule
Rational::Rational(double num, int den) : m_num(num), m_den(den) {}
*/

Rational::operator double() const
{ 
    return 1.0 * m_num / m_den;
}

Rational & Rational::operator+=(Rational const & other)
{
    auto lcm = std::lcm(m_den, other.m_den);

    m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);

    m_den = lcm;

    reduce();

    return *this;
}

Rational & Rational::operator-=(Rational const & other) 
{ 
    return *this += Rational(other.m_num * -1, other.m_den);
}

Rational & Rational::operator*=(Rational const & other)
{
    m_num *= other.m_num;

    m_den *= other.m_den;

    reduce();

    return *this;
}

Rational & Rational::operator/=(Rational const & other) 
{ 
    return *this *= Rational(other.m_den, other.m_num);
}

Rational const Rational::operator++(int) { auto x = *this; *this += 1; return x; }

Rational const Rational::operator--(int) { auto x = *this; *this -= 1; return x; }

Rational & Rational::operator++() { *this += 1; return *this; }

Rational & Rational::operator--() { *this -= 1; return *this; }

Rational operator+ (Rational lhs, Rational const & rhs) { return lhs += rhs; }

Rational operator- (Rational lhs, Rational const & rhs) { return lhs -= rhs; }

Rational operator* (Rational lhs, Rational const & rhs) { return lhs *= rhs; }

Rational operator/ (Rational lhs, Rational const & rhs) { return lhs /= rhs; }

std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs)
{
    return lhs.m_num * rhs.m_den <=> rhs.m_num * lhs.m_den;
}

bool operator==(Rational const & lhs, Rational const & rhs)
{
    return !(lhs < rhs) && !(rhs < lhs);
}

std::istream & operator>>(std::istream & stream, Rational & rational)
{
    return (stream >> rational.m_num).ignore() >> rational.m_den;
}

std::ostream & operator<<(std::ostream & stream, Rational const & rational)
{
    return stream << rational.m_num << '/' << rational.m_den;
}

void Rational::reduce()
{
    if (m_den < 0)
    {
        m_num = -m_num;

        m_den = -m_den;
    }

    auto gcd = std::gcd(m_num, m_den);

    m_num /= gcd;

    m_den /= gcd;
}
