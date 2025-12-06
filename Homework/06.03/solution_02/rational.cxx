export module rational;

import <compare>;
import <iostream>;

export namespace numbers {

class Rational {
public:
    Rational(int num = 0, int den = 1);

    explicit operator double() const;

    Rational& operator+=(Rational const& other);
    Rational& operator-=(Rational const& other);
    Rational& operator*=(Rational const& other);
    Rational& operator/=(Rational const& other);

    Rational const reverse();

    Rational const operator++(int);
    Rational const operator--(int);
    Rational& operator++();
    Rational& operator--();

    friend Rational operator+(Rational lhs, Rational const& rhs);
    friend Rational operator-(Rational lhs, Rational const& rhs);
    friend Rational operator*(Rational lhs, Rational const& rhs);
    friend Rational operator/(Rational lhs, Rational const& rhs);

    friend std::strong_ordering operator<=>(Rational const& lhs, Rational const& rhs);
    friend bool operator==(Rational const& lhs, Rational const& rhs);

    friend std::istream& operator>>(std::istream& stream, Rational& rational);
    friend std::ostream& operator<<(std::ostream& stream, Rational const& rational);

private:
    void reduce();

    int m_num = 0;
    int m_den = 1;
};

}
