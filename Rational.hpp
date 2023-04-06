#pragma once
#include <cmath>

// Prime Factorization

int GreatestCommonDivisor(const int &n, const int &m)
{
    if (std::min(n, m) == 1)
    {
        return 1;
    }

    if (n == m)
    {
        return n;
    }

    return GreatestCommonDivisor(std::max(n, m) - std::min(n, m), std::min(n, m));
}

int LeastCommonMultiple(const int &n, const int &m)
{
}

class Rational
{
private:
    int numerator;
    int denumerator;

public:
    Rational(const int &num, const int &den)
    {
        numerator = num;
        denumerator = den;
    }

    ~Rational();
};