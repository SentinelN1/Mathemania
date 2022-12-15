#include <complex>
#include <cmath>
#include <iostream>
// #include "polynomial.h"

using std::cin;
using std::complex;
using std::cout;
using std::endl;

complex<double> function(const complex<double> &z)
{
    // return pow(z, 5) + pow(z, 2) - z + 1.0;
    return pow(z, 3) - 1.0;
}

complex<double> derivetive(const complex<double> z)
{
    const double EPSILON = 1e-12;
    return (function(z + EPSILON) - function(z)) / EPSILON;
}

// x(n+1) = x(n) - f(x(n)) / f'(x(n))
complex<double> root(const complex<double> &z)
{
    const double EPSILON = 1e-12;
    if (std::abs(function(z)) <= EPSILON)
    {
        return z;
    }
    return root(z - function(z) / derivetive(z));
}

int main()
{
    complex<double> z(-3, 3);
    complex<double> r = root(z);
    cout << z << endl;
    cout << r << endl;
    cout << function(r) << endl;
    return 0;
}
