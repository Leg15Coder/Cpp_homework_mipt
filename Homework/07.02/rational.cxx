export module rational;

import <compare>;
import <iostream>;

export namespace numbers {

class Rational {
public:
    Rational(int num = 0, int den = 1);

    explicit operator double() const;

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    Rational const reverse();

    Rational const operator++(int);
    Rational const operator--(int);
    Rational& operator++();
    Rational& operator--();

    friend Rational operator+(Rational lhs, const Rational& rhs);
    friend Rational operator-(Rational lhs, const Rational& rhs);
    friend Rational operator*(Rational lhs, const Rational& rhs);
    friend Rational operator/(Rational lhs, const Rational& rhs);

    friend std::strong_ordering operator<=>(const Rational& lhs, const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);

    friend std::istream& operator>>(std::istream& stream, Rational& rational);
    friend std::ostream& operator<<(std::ostream& stream, const Rational& rational);

private:
    void reduce();

    int m_num = 0;
    int m_den = 1;
};

}
