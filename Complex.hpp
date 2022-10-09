#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class Complex
{
public:
    double real;
    double imaginary;
    double modulus;
    double argument;

    // Constructor
    Complex(const double x = 0, const double y = 0, char form[] = "algebraic")
    {
        if (form == "algebraic")
        {
            real = x;
            imaginary = y;
        }
        else if (form == "polar")
        {
            modulus = x;
            argument = y;
            real = x * cos(y);
            imaginary = y * sin(y);
        }
    }

    // Equality
    bool operator==(const Complex other) const
    {
        return (real == other.real && imaginary == other.imaginary);
    }

    // Unequality
    bool operator!=(const Complex other) const
    {
        // return (x+yi != a+bi);
        return (real != other.real || imaginary != other.imaginary);
    }

    friend std::ostream &operator<<(std::ostream &os, const Complex complex)
    {
        os << complex.real << " + " << complex.imaginary << "i";
        return os;
    }

    // Absolute value
    double Abs() const
    {
        return sqrt(real * real + imaginary * imaginary);
    }

    // Argument
    double Arg() const
    {
        return atan2(imaginary, real);
    }

    // Unary plus
    Complex operator+() const
    {
        return Complex(real, imaginary);
    }

    // Binary plus -- Addition
    friend Complex operator+(const Complex a, const Complex b)
    {
        return Complex(a.real + b.real, a.imaginary + b.imaginary);
    }

    // Increment
    Complex operator+=(const Complex complex)
    {
        real += complex.real;
        imaginary += complex.imaginary;
        return Complex(real, imaginary);
    }

    // Unary Minus
    Complex operator-() const
    {
        return Complex(-real, -imaginary);
    }

    // Binary Minus -- Subtraction
    friend Complex operator-(const Complex a, const Complex b)
    {
        return Complex(a.real - b.real, a.imaginary - b.imaginary);
    }

    // Decrement
    Complex operator-=(const Complex complex)
    {
        real -= complex.real;
        imaginary -= complex.imaginary;
        return Complex(real, imaginary);
    }

    // Multiplication
    friend Complex operator*(const Complex a, const Complex b)
    {
        return Complex(a.real * b.real - a.imaginary * b.imaginary, a.real * b.imaginary + a.imaginary * b.real);
    }

    Complex operator*=(const Complex complex)
    {
        real = real * complex.real - imaginary * complex.imaginary;
        imaginary = real * complex.imaginary + imaginary * complex.real;
        return Complex(real, imaginary);
    }

    // Complex Conjugate (x - yi)
    Complex Conjugate() const
    {
        return Complex(real, -imaginary);
    }

    //
    Complex Reciprocal() const
    {
        double abs2 = real * real + imaginary * imaginary;
        if (abs2 != 0)
        {
            return Complex(real / abs2, -imaginary / abs2);
        }
        std::cout << "Division by zero ecountered.\n";
        exit(0);
    }

    friend Complex operator/(const Complex a, const Complex b)
    {
        return a * b.Reciprocal();
    }
};

#define M_I Complex(0, 1)

double Re(const Complex complex)
{
    return complex.real;
}

double Im(const Complex complex)
{
    return complex.imaginary;
}

double Abs(const Complex complex)
{
    return complex.Abs();
}

double Arg(const Complex complex)
{
    return complex.Arg();
}

Complex Log(const Complex complex, const Complex base = M_E)
{
    if (Abs(complex) != 0)
    {
        if (base == M_E)
        {
            return Complex(log(Abs(complex)), Arg(complex));
        }

        return Log(complex) / Log(base);
    }
    std::cout << "Log(0) is undefined.\n";
    exit(0);
}

Complex Exp(const Complex complex)
{
    return exp(complex.real) * Complex(1, complex.imaginary, "polar");
}

Complex Pow(const Complex complex, const Complex power)
{
    double abs = Abs(complex);
    double arg = Arg(complex);
    if (Im(power) == 0 && (abs != 0 || Re(power) > 0))
    {
        return Complex(pow(abs, Re(power)), Re(power) * arg, "polar");
    }

    return Exp(Log(complex) * power);
}

Complex Sin(const Complex complex)
{
    return Complex(sin(complex.real) * cosh(complex.imaginary), cos(complex.real) * sinh(complex.imaginary));
}

Complex Cos(const Complex complex)
{
    return Complex(cos(complex.real) * cosh(complex.imaginary), -sin(complex.real) * sinh(complex.imaginary));
}
