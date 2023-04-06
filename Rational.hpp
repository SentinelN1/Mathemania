#pragma once
#include <iostream>
#include <cmath>
#include <map>

// Prime Factorization
// prime: 6736271637627637271, 70650451, 4424293, 2077811, 909061, 7277327
void Factrorization(const long long int &n, std::map<long long int, long long int> &factors)
{
    for (long long int k = sqrt(n); k > 1; --k)
    {
        if (n % k == 0)
        {
            Factrorization(k, factors);
            Factrorization(n / k, factors);
            return;
        }
    }
    ++factors[n];
}

int GreatestCommonDivisor(const int &n, const int &m)
{
    // 0, 0
    // 0, n
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
    return n * m / GreatestCommonDivisor(n, m);
}

class Rational
{
private:
    int numerator, denumerator;

public:
    Rational(const int &num, const int &den)
    {
        numerator = num;
        denumerator = den;
    }

    ~Rational();

    Rational operator+(const Rational &other) const
    {
        int num = numerator * other.denumerator + other.numerator * denumerator;
        int den = denumerator * other.denumerator;
        int gcd = GreatestCommonDivisor(num, den);
        return Rational(num / gcd, den / gcd);
    }

    Rational operator*(const Rational &other) const
    {
        int num = numerator * other.numerator;
        int den = denumerator * other.denumerator;
        int gcd = GreatestCommonDivisor(num, den);
        return Rational(num / gcd, den / gcd);
    }

    void Print()
    {
        std::cout << numerator << "/" << denumerator << "\n";
    }
};