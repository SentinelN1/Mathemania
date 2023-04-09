#pragma once

#include <cmath>
#include <iostream>

namespace complex
{
    enum Form
    {
        cartesian,
        polar
    };

    template <typename T = double>
    class Complex
    {
    private:
        T real, imaginary;
        // Form form;

    public:
        // Is a number purely real?
        bool IsReal() const
        {
            return imaginary == 0;
        }

        // Is a number purely imaginary?
        bool IsImaginary() const
        {
            return real == 0;
        }

        // Real part of a complex number
        T Real() const
        {
            return real;
        }

        explicit operator double() const
        {
            return real;
        }

        // Imaginary part of a complex number
        T Imaginary() const
        {
            return imaginary;
        }

        // Absolute value of a complex number
        double Abs() const
        {
            return sqrt(real * real + imaginary * imaginary);
        }

        // Argument of a complex number
        double Arg() const
        {
            return atan2(imaginary, real);
        }

        // Constructor
        Complex(const T &x = 0, const T &y = 0, Form form = cartesian)
        {
            switch (form)
            {
            case cartesian:
                real = x;
                imaginary = y;
                break;
            case polar:
                real = x * cos(y);
                imaginary = x * sin(y);
                break;
            default:
                real = x;
                imaginary = y;
                break;
            }
        }

        // Copy Constructor
        Complex(const Complex &complex)
        {
            if (this != &complex)
            {
                real = complex.real;
                imaginary = complex.imaginary;
            }
        }

        // Move Constructor
        Complex(Complex &&complex) noexcept
        {
            if (this != &complex)
            {
                real = complex.real;
                imaginary = complex.imaginary;
                complex.real = 0;
                complex.imaginary = 0;
            }
        }

        // Copy Assignment Operator
        Complex &operator=(const Complex &complex)
        {
            if (this != &complex)
            {
                real = complex.real;
                imaginary = complex.imaginary;
            }
            return *this;
        }

        // Move Assignment Operator
        Complex &operator=(Complex &&complex) noexcept
        {
            if (this != &complex)
            {
                real = complex.real;
                imaginary = complex.imaginary;
                complex.real = 0;
                complex.imaginary = 0;
            }
            return *this;
        }

        // Equality operator
        friend bool operator==(const Complex &complex1, const Complex &complex2)
        {
            return (complex1.real == complex2.real && complex1.imaginary == complex2.imaginary);
        }

        // Inequality operator
        friend bool operator!=(const Complex &complex1, const Complex &complex2)
        {
            return (complex1.real != complex2.real || complex1.imaginary != complex2.imaginary);
        }

        // Stream output
        friend std::ostream &operator<<(std::ostream &os, const Complex<T> &complex)
        {
            if (complex.IsReal())
            {
                os << complex.real;
                return os;
            }
            if (complex.IsImaginary())
            {
                if (complex.imaginary == -1)
                {
                    os << "-i";
                    return os;
                }
                if (complex.imaginary == 1)
                {
                    os << "i";
                    return os;
                }
                os << complex.imaginary << "i";
                return os;
            }
            os << complex.real;
            if (complex.imaginary > 0)
            {
                os << "+";
                if (complex.imaginary == 1)
                {
                    os << "i";
                    return os;
                }
                os << complex.imaginary << "i";
                return os;
            }
            if (complex.imaginary == -1)
            {
                os << "-i";
                return os;
            }
            os << complex.imaginary << "i";
            return os;
        }

        // Unary plus
        Complex operator+() const
        {
            return Complex(real, imaginary);
        }

        // Unary Minus
        Complex operator-() const
        {
            return Complex(-real, -imaginary);
        }

        // Addition
        friend Complex operator+(const Complex &complex1, const Complex &complex2)
        {
            return Complex(complex1.real + complex2.real, complex1.imaginary + complex2.imaginary);
        }

        // Subtraction
        friend Complex operator-(const Complex &complex1, const Complex &complex2)
        {
            return Complex(complex1.real - complex2.real, complex1.imaginary - complex2.imaginary);
        }

        // Multiplication
        friend Complex operator*(const Complex &complex1, const Complex &complex2)
        {
            return Complex(complex1.real * complex2.real - complex1.imaginary * complex2.imaginary,
                           complex1.real * complex2.imaginary + complex1.imaginary * complex2.real);
        }

        // Increment
        Complex &operator+=(const Complex &other)
        {
            real += other.real;
            imaginary += other.imaginary;
            return *this;
        }

        // Decrement
        Complex &operator-=(const Complex &other)
        {
            real -= other.real;
            imaginary -= other.imaginary;
            return *this;
        }
        //
        //        void operator*=(const Complex &complex) {
        //            *this = *this * complex;
        //        }

        // Complex Conjugate
        Complex Conjugate() const
        {
            return Complex(real, -imaginary);
        }

        // Complex Reciprocal
        Complex Reciprocal() const
        {
            T abs2 = real * real + imaginary * imaginary;
            if (abs2 != 0)
            {
                throw std::exception();
            }
            return Complex(real / abs2, -imaginary / abs2);
        }

        // Division operator
        friend Complex operator/(const Complex &complex1, const Complex &complex2)
        {
            return complex1 * complex2.Reciprocal();
        }
    };

    template <typename T>
    T Re(const Complex<T> &complex)
    {
        return complex.Real();
    }

    template <typename T>
    T Im(const Complex<T> &complex)
    {
        return complex.Imaginary();
    }

    template <typename T>
    T Abs(const Complex<T> &complex)
    {
        return complex.Abs();
    }

    template <typename T>
    T Arg(const Complex<T> &complex)
    {
        return complex.Arg();
    }

    template <typename T>
    Complex<T> Conjugate(const Complex<T> &complex)
    {
        return complex.Conjugate();
    }

    template <typename T>
    Complex<T> Reciprocal(const Complex<T> &complex)
    {
        return complex.Reciprocal();
    }

    // Complex Valued Logarithm
    template <typename T>
    Complex<T> Log(const Complex<T> &complex, const Complex<T> &base = M_E)
    {
        if (complex == 0)
        {
            throw std::exception();
        }
        if (base != M_E)
        {
            return Log(complex) / Log(base);
        }
        return Complex<T>(log(Abs(complex)), Arg(complex));
    }

    // Complex valued exponent
    template <typename T>
    Complex<T> Exp(const Complex<T> &exponent, const Complex<T> &base = M_E)
    {
        if (base == M_E)
        {
            return exp(Re(exponent)) * Complex<T>(1, Im(exponent), polar);
        }
        return Exp(Log(base) * exponent);
    }

    // Computes complex number raised to the complex power
    template <typename T>
    Complex<T> Pow(const Complex<T> &base, const Complex<T> &power)
    {
        if (base == 0 && Re(power) > 0 && Im(power) == 0)
        {
            return 0;
        }
        return Exp(Log(base) * power);
    }

    template <typename T>
    Complex<T> Sin(const Complex<T> &complex)
    {
        return Complex<T>(sin(Re(complex)) * cosh(Im(complex)), cos(Re(complex)) * sinh(Im(complex)));
    }

    template <typename T>
    Complex<T> Cos(const Complex<T> &complex)
    {
        return Complex<T>(cos(Re(complex)) * cosh(Im(complex)), -sin(Re(complex)) * sinh(Im(complex)));
    }

    template <typename T>
    Complex<T> Tan(const Complex<T> &complex)
    {
        return Sin(complex) / Cos(complex);
    }

    template <typename T>
    Complex<T> Ctg(const Complex<T> &complex)
    {
        return Cos(complex) / Sin(complex);
    }

    template <typename T>
    Complex<T> Sec(const Complex<T> &complex)
    {
        return Cos(complex).Reciprocal();
    }

    template <typename T>
    Complex<T> Csc(const Complex<T> &complex)
    {
        return Sin(complex).Reciprocal();
    }

    template <typename T>
    Complex<T> Sinh(const Complex<T> &complex)
    {
        return 0;
    }

    template <typename T>
    Complex<T> Cosh(const Complex<T> &complex)
    {
        return 0;
    }
}