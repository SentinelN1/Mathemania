#pragma once

#ifndef _COMPLEX
#define _COMPLEX

#include <iostream>
#include <cmath>

class complex
{
private:
    double real;
    double imaginary;

public:
    // Constructor
    complex(const double &x = 1, const double &y = 0, const bool &polar = false)
    {
        if (polar)
        {
            real = x * cos(y);
            imaginary = x * sin(y);
        }
        else
        {
            real = x;
            imaginary = y;
        }
    }

    // Copy
    complex(const complex &z)
    {
    }

    // Destructor
    ~complex() {}

    // Real part of a complex number
    static double Re(const complex &z)
    {
        return z.real;
    }

    // Imaginary part of a complex number
    static double Im(const complex &z)
    {
        return z.imaginary;
    }

    // Absolute value of a complex number
    static double Abs(const complex &z)
    {
        return sqrt(z.real * z.real + z.imaginary * z.imaginary);
    }

    // Returns argument of a complex number
    static double Arg(const complex &z)
    {
        return atan2(z.imaginary, z.real);
    }

    // Equality operator
    bool operator==(const complex &z) const
    {
        return (real == z.real && imaginary == z.imaginary);
    }

    // Inequality operator
    bool operator!=(const complex &z) const
    {
        return !(*this == z);
    }

    // Stream output
    friend std::ostream &operator<<(std::ostream &os, const complex &z)
    {
        os << z.real;
        if (z.imaginary >= 0)
        {
            os << "+";
        }
        os << z.imaginary << "i";
        return os;
    }

    // Unary plus
    complex operator+() const
    {
        return complex(real, imaginary);
    }

    // Addition
    friend complex operator+(const complex &z, const complex &c)
    {
        return complex(z.real + c.real, z.imaginary + c.imaginary);
    }

    // Increment
    void operator+=(const complex &z)
    {
        real += z.real;
        imaginary += z.imaginary;
    }

    // Unary Minus
    complex operator-() const
    {
        return complex(-real, -imaginary);
    }

    // Subtraction
    friend complex operator-(const complex &z, const complex &c)
    {
        return complex(z.real - c.real, z.imaginary - c.imaginary);
    }

    // Decrement
    void operator-=(const complex &z)
    {
        real -= z.real;
        imaginary -= z.imaginary;
    }

    // Multiplication
    friend complex operator*(const complex &z, const complex &c)
    {
        return complex(z.real * c.real - z.imaginary * c.imaginary, z.real * c.imaginary + z.imaginary * c.real);
    }

    void operator*=(const complex &z)
    {
        double tmp = real;
        real = tmp * Re(z) - imaginary * Im(z);
        imaginary = tmp * Im(z) + imaginary * Re(z);
    }

    // Complex Conjugate
    static complex Conjugate(const complex &z)
    {
        return complex(Re(z), -Im(z));
    }

    // Complex Reciprocal
    static complex Reciprocal(const complex &z)
    {
        double abs2 = Re(z) * Re(z) + Im(z) * Im(z);

        if (abs2 != 0)
        {
            return complex(Re(z) / abs2, -Im(z) / abs2);
        }

        // throw "Division by zero";
    }

    // Division operator [TESTED]
    friend complex operator/(const complex &z, const complex &c)
    {
        return z * Reciprocal(c);
    }

    // Calculates logarithm of a complex number. By default base is set to e (~2.7182)
    static complex Log(const complex &z, const complex &c = M_E)
    {
        if (z != 0)
        {
            if (c != M_E)
            {
                return Log(z) / Log(c);
            }

            return complex(log(Abs(z)), Arg(z));
        }
    }

    // Raises e to complex power
    static complex Exp(const complex &z)
    {
        return exp(Re(z)) * complex(1, Im(z), true);
    }

    // Computes complex number raised to the complex power
    static complex Pow(const complex &z, const complex &c)
    {
        if (z == 0 && Re(c) > 0 && Im(c) == 0)
        {
            return 0;
        }
        return Exp(Log(z) * c);
    }

    static complex Sin(const complex &z)
    {
        return complex(sin(Re(z)) * cosh(Im(z)), cos(Re(z)) * sinh(Im(z)));
    }

    static complex Cos(const complex &z)
    {
        return complex(cos(Re(z)) * cosh(Im(z)), -sin(Re(z)) * sinh(Im(z)));
    }

    static complex Tan(const complex &z)
    {
        return Sin(z) / Cos(z);
    }

    static complex Ctg(const complex &z)
    {
        return Cos(z) / Sin(z);
    }
};

#endif
