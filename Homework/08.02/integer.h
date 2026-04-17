#ifndef INTEGER_H
#define INTEGER_H

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstddef>
#include <limits>
#include <utility>

using namespace std::literals;

class Integer
{
public:
    using digit_t = long long int;

    Integer();
    Integer(digit_t digit);
    Integer(std::string const & string);

    void swap(Integer & other);

    Integer & operator+=(Integer other);
    Integer & operator-=(Integer other);
    Integer & operator*=(Integer other);
    Integer & operator/=(Integer other);
    Integer & operator%=(Integer other);

    Integer pow(unsigned int p) const;
    int sign() const;
    Integer abs() const;

    const Integer operator++(int);
    const Integer operator--(int);
    Integer & operator++();
    Integer & operator--();

    friend Integer operator+(Integer lhs, Integer const & rhs);
    friend Integer operator-(Integer lhs, Integer const & rhs);
    friend Integer operator*(Integer lhs, Integer const & rhs);
    friend Integer operator/(Integer lhs, Integer const & rhs);
    friend Integer operator%(Integer lhs, Integer const & rhs);

    friend bool operator<(Integer const & lhs, Integer const & rhs);
    friend bool operator>(Integer const & lhs, Integer const & rhs);
    friend bool operator<=(Integer const & lhs, Integer const & rhs);
    friend bool operator>=(Integer const & lhs, Integer const & rhs);
    friend bool operator==(Integer const & lhs, Integer const & rhs);
    friend bool operator!=(Integer const & lhs, Integer const & rhs);

    friend std::istream & operator>>(std::istream & stream, Integer & integer);
    friend std::ostream & operator<<(std::ostream & stream, Integer const & integer);

    friend Integer sqrt(Integer const & x);
    friend Integer multiply(Integer const & x, Integer const & y);

private:
    void parse(std::string const & string);
    void reduce();
    Integer & add(Integer const & other);
    Integer & subtract(Integer const & other);
    bool less(Integer const & other) const;

    bool m_is_negative = false;
    std::vector < digit_t > m_digits;
    std::size_t m_size = 0;

    static inline auto s_size = 1'000uz;
	static inline auto s_step = std::numeric_limits < digit_t > ::digits10 / 2;
	static inline auto s_base = static_cast < digit_t > (std::pow(10, s_step));
};

#endif
