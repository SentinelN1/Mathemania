#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

class Complex
{
private:
    double real, imaginary;

public:
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
            // modulus = x;
            // argument = y;
            real = x * cos(y);
            imaginary = y * sin(y);
        }
    }

    double Re() const
    {
        return real;
    }

    double Im() const
    {
        return imaginary;
    }

    // Equality
    bool operator==(const Complex &other) const
    {
        return (real == other.real && imaginary == other.imaginary);
    }

    // Inequality
    bool operator!=(const Complex &other) const
    {
        // return !(this == other);
        return (real != other.real || imaginary != other.imaginary);
    }

    friend std::ostream &operator<<(std::ostream &os, const Complex &complex)
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

    // Addition
    friend Complex operator+(const Complex &a, const Complex &b)
    {
        return Complex(a.real + b.real, a.imaginary + b.imaginary);
    }

    // Increment
    void operator+=(const Complex &other)
    {
        this->real += other.real;
        this->imaginary += other.imaginary;
    }

    // Unary Minus
    Complex operator-() const
    {
        return Complex(-real, -imaginary);
    }

    // Subtraction
    friend Complex operator-(const Complex &a, const Complex &b)
    {
        return Complex(a.real - b.real, a.imaginary - b.imaginary);
    }

    // Decrement
    void operator-=(const Complex &other)
    {
        this->real -= other.real;
        this->imaginary -= other.imaginary;
    }

    // Multiplication
    friend Complex operator*(const Complex &a, const Complex &b)
    {
        return Complex(a.real * b.real - a.imaginary * b.imaginary, a.real * b.imaginary + a.imaginary * b.real);
    }

    void operator*=(const Complex &other)
    {
        this->real = real * other.real - imaginary * other.imaginary;
        this->imaginary = real * other.imaginary + imaginary * other.real;
    }

    // Complex Conjugate (x - yi)
    Complex Conjugate() const
    {
        return Complex(real, -imaginary);
    }

    // Complex reciprocal (Conj(z) / Abs(z)^2)
    Complex Reciprocal() const
    {
        double abs2 = real * real + imaginary * imaginary;

        if (abs2 == 0)
        {
            throw "Division by zero";
        }

        return Complex(real / abs2, -imaginary / abs2);
    }

    friend Complex operator/(const Complex &a, const Complex &b)
    {
        return a * b.Reciprocal();
    }
};

double Re(const Complex &complex)
{
    return complex.Re();
}

double Im(const Complex &complex)
{
    return complex.Im();
}

double Abs(const Complex &complex)
{
    return complex.Abs();
}

double Arg(const Complex &complex)
{
    return complex.Arg();
}

Complex Conjugate(const Complex &complex)
{
    return complex.Conjugate();
}

Complex Reciprocal(const Complex &complex)
{
    return complex.Reciprocal();
}

// Complex logarithm, by default logarithm base is set to e = 2.7182818284590452354
Complex Log(const Complex &complex, const Complex &base = M_E)
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

Complex Exp(const Complex &complex)
{
    return exp(Re(complex)) * Complex(1, Im(complex), "polar");
}

Complex Pow(const Complex &complex, const Complex &power)
{
    double abs = Abs(complex);
    double arg = Arg(complex);
    if (Im(power) == 0 && (abs != 0 || Re(power) > 0))
    {
        return Complex(pow(abs, Re(power)), Re(power) * arg, "polar");
    }

    return Exp(Log(complex) * power);
}

Complex Sin(const Complex &complex)
{
    return Complex(sin(complex.Re()) * cosh(complex.Im()), cos(complex.Re()) * sinh(complex.Im()));
}

Complex Cos(const Complex &complex)
{
    return Complex(cos(complex.Re()) * cosh(complex.Im()), -sin(complex.Re()) * sinh(complex.Im()));
}
