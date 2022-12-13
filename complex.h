#pragma once
#define M_E 2.71828182846
#include <iostream>
#include <cmath>

class complex
{
private:
    double real;
    double imaginary;

public:
    // Constructor
    complex(const double &x = 0, const double &y = 0, const bool &polar = false)
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

#define C_I complex(0, 1)

    bool IsReal() const
    {
        return imaginary == 0;
    }

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
    friend std::ostream &operator<<(std::ostream &os, const complex &number)
    {
        if (number.real != 0)
        {
            os << number.real;

            if (number.imaginary != 0)
            {
                if (number.imaginary > 0)
                {
                    os << "+";
                }
                os << number.imaginary << "i";
                return os;
            }

            os << number.real;
            return os;
        }
        if (number.imaginary != 0)
        {
            os << number.imaginary << "i";
            return os;
        }
        os << 0;
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

        std::cout << "Division by zero\n";
        exit(163);
    }

    // Division operator [TESTED]
    friend complex operator/(const complex &z, const complex &c)
    {
        return z * Reciprocal(c);
    }

    // Calculates logarithm of a complex number. By default base is set to e (~2.7182)
    static complex Log(const complex &number, const complex &base = M_E)
    {
        if (number != 0)
        {
            if (base != M_E)
            {
                return Log(number) / Log(base);
            }

            return complex(log(Abs(number)), Arg(number));
        }
        std::cout << "Log(0) is undefined\n";
        exit(185); // Replace with exception
    }

    // Raises e to complex power
    static complex Exp(const complex &exponent, const complex &base = M_E)
    {
        if (base == M_E)
        {
            return exp(Re(exponent)) * complex(1, Im(exponent), true);
        }
        return Exp(Log(base) * exponent);
    }

    // Computes complex number raised to the complex power
    static complex Pow(const complex &base, const complex &power)
    {
        if (base == 0 && Re(power) > 0 && Im(power) == 0)
        {
            return 0;
        }
        return Exp(Log(base) * power);
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
