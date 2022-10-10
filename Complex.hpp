#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class Complex
{
private:
    double re, im;

public:
    // Constructor
    Complex(const double &x = 1, const double &y = 0, bool polarForm = false)
    {
        if (polarForm)
        {
            re = x * cos(y);
            im = x * sin(y);
        }
        else
        {
            re = x;
            im = y;
        }
    }

    // Real part of a complex number [TESTED]
    static double Re(const Complex &complex)
    {
        return complex.re;
    }

    // Imaginary part of a complex number [TESTED]
    static double Im(const Complex &complex)
    {
        return complex.im;
    }

    // Absolute value of a complex number [TESTED]
    static double Abs(const Complex &complex)
    {
        return sqrt(complex.re * complex.re + complex.im * complex.im);
    }

    // Returns argument of a complex number [TESTED]
    static double Arg(const Complex &complex)
    {
        return atan2(complex.im, complex.re);
    }

    // Equality operator [TESTED]
    bool operator==(const Complex &other) const
    {
        return (re == other.re && im == other.im);
    }

    // Inequality operator [TESTED]
    bool operator!=(const Complex &other) const
    {
        // return !(this == other);
        return (re != other.re || im != other.im);
    }

    // Stream output [TESTED]
    friend std::ostream &operator<<(std::ostream &os, const Complex &complex)
    {
        os << complex.re;
        if (complex.im >= 0)
        {
            os << "+";
        }
        os << complex.im << "i";
        return os;
    }

    // Unary plus [TESTED]
    Complex operator+() const
    {
        return Complex(re, im);
    }

    // Addition [TESTED]
    friend Complex operator+(const Complex &complex, const Complex &other)
    {
        return Complex(complex.re + other.re, complex.im + other.im);
    }

    // Increment [TESTED]
    void operator+=(const Complex &other)
    {
        re += other.re;
        im += other.im;
    }

    // Unary Minus [TESTED]
    Complex operator-() const
    {
        return Complex(-re, -im);
    }

    // Subtraction [TESTED]
    friend Complex operator-(const Complex &complex, const Complex &other)
    {
        return Complex(complex.re - other.re, complex.im - other.im);
    }

    // Decrement [TESTED]
    void operator-=(const Complex &other)
    {
        re -= other.re;
        im -= other.im;
    }

    // Multiplication [TESTED]
    friend Complex operator*(const Complex &complex, const Complex &other)
    {
        return Complex(complex.re * other.re - complex.im * other.im, complex.re * other.im + complex.im * other.re);
    }

    // [TESTED]
    void operator*=(const Complex &other)
    {
        double tmp = re;
        re = tmp * other.re - im * other.im;
        im = tmp * other.im + im * other.re;
    }

    // Complex Conjugate (x - yi) [TESTED]
    static Complex Conjugate(const Complex &complex)
    {
        return Complex(complex.re, -complex.im);
    }

    // Complex reciprocal (Conj(z) / Abs(z)^2) [TESTED]
    static Complex Reciprocal(const Complex &complex)
    {
        double abs2 = complex.re * complex.re + complex.im * complex.im;

        if (abs2 == 0)
        {
            throw "Division by zero";
        }

        return Complex(complex.re / abs2, -complex.im / abs2);
    }

    // Division operator [TESTED]
    friend Complex operator/(const Complex &complex, const Complex &other)
    {
        return complex * Reciprocal(other);
    }

    // Calculates logarithm o fa complex number. By default base is set to e (~2.7182)
    static Complex Log(const Complex &complex, const Complex &base = M_E)
    {
        if (complex == 0)
        {
            throw "Logarithm of 0 is undefined";
        }

        {
            if (base == M_E)
            {
                return Complex(log(Abs(complex)), Arg(complex));
            }

            return Log(complex) / Log(base);
        }
    }

    // Raises e to complex power
    static Complex Exp(const Complex &complex)
    {
        return exp(Re(complex)) * Complex(1, Im(complex), true);
    }

    // Computes complex number raised to the complex power
    static Complex Pow(const Complex &complex, const Complex &power)
    {
        if (complex == 0 && power.re > 0 && power.im == 0)
        {
            return 0;
        }
        return Exp(Log(complex) * power);
    }

    static Complex Sin(const Complex &complex)
    {
        return Complex(sin(complex.re) * cosh(complex.im), cos(complex.re) * sinh(complex.im));
    }

    static Complex Cos(const Complex &complex)
    {
        return Complex(cos(complex.re) * cosh(complex.im), -sin(complex.re) * sinh(complex.im));
    }

    static Complex Tan(const Complex &complex)
    {
        return Sin(complex) / Cos(complex);
    }

    static Complex Ctg(const Complex &complex)
    {
        return Cos(complex) / Sin(complex);
    }
};
