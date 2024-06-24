#ifndef MATHEMANIA_RATIONAL_H_
#define MATHEMANIA_RATIONAL_H_
#include <iostream>

template <typename T>
bool IsPrime(const T &n);

template <typename T>
T GreatestCommonDivisor(const T &, const T &);

template <typename T>
T LeastCommonMultiple(const T &, const T &);

template <typename T>
class Rational
{
private:
    T numerator_;
    T denominator_;

public:
    Rational(const T & = 0, const T & = 1);
    ~Rational();
    Rational(const Rational<T> &);

    template <typename Y>
    friend std::ostream &operator<<(std::ostream &, const Rational<Y> &);
    Rational<T> operator+(const Rational<T> &);
    Rational<T> operator*(const Rational<T> &);
    Rational<T> operator*(const T &);
};


// Calculate n mod m
template <typename T>
T modulo(const T &n, const T &m)
{
    if ()
    {
    }
}

template <typename T>
T GreatestCommonDivisor(const T &n, const T &m)
{
    if (n % m)

        if (std::abs(n) == 1 || std::abs(m) == 1)
        {
            return 1;
        }
    if (std::abs(n) == std::abs(m))
    {
        return std::abs(n);
    }
    if (std::abs(n) > std::abs(m))
    {
        return GreatestCommonDivisor(std::abs(n) - std::abs(m), std::abs(m));
    }
    if (std::abs(n) < std::abs(m))
    {
        return GreatestCommonDivisor(std::abs(n), std::abs(m) - std::abs(n));
    }
    return 1;
}

template <typename T>
T LeastCommonMultiple(const T &n, const T &m)
{
    return std::abs(n * m) / GreatestCommonDivisor(n, m);
}

template <typename T>
Rational<T>::Rational(const T &numerator, const T &denominator)
{
    if (denominator == 0)
    {
        throw(std::exception);
    }

    numerator_ = numerator;
    denominator_ = denominator;

    T gcd = GreatestCommonDivisor(numerator, denominator);
    numerator_ = numerator_ / gcd;
    denominator_ = denominator_ / gcd;

    if (denominator < 0)
    {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}

template <typename T>
Rational<T>::~Rational() = default;

template <typename T>
std::ostream &operator<<(std::ostream &os, const Rational<T> &rational)
{
    os << rational.numerator_;
    if (rational.denominator_ != 1)
    {
        os << "/" << rational.denominator_;
    }
    return os;
}

template <typename T>
Rational<T> Rational<T>::operator+(const Rational<T> &other)
{
    T numerator = numerator_ * other.denominator_ + other.numerator_ * denominator_;
    T denominator = denominator_ * other.denominator_;
    return Rational<T>(numerator, denominator);
}

template <typename T>
Rational<T> Rational<T>::operator*(const Rational<T> &other)
{
    return Rational<T>(numerator_ * other.numerator_, denominator_ * other.denominator_);
}


#endif