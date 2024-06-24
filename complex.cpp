#ifndef MATHEMANIA_COMPLEX_CPP_
#define MATHEMANIA_COMPLEX_CPP_

#include "complex.h"

#include <cmath>

template <typename T>
void Complex<T>::clear()
{
    real_ = T();
    imaginary_ = T();
}

template <typename T>
T Complex<T>::Real() const
{
    return real_;
}

template <typename T>
T Complex<T>::Imaginary() const
{
    return imaginary_;
}

// Absolute value
template <typename T>
T Complex<T>::Abs() const
{
    return sqrt(real_ * real_ + imaginary_ * imaginary_);
}

template <typename T>
bool Complex<T>::IsPurelyReal() const
{
    return imaginary_ == 0;
}

template <typename T>
bool Complex<T>::IsPurelyImaginary() const
{
    return real_ == 0;
}

// Argument
template <typename T>
T Complex<T>::Arg() const
{
    return atan2(imaginary_, real_);
}

// Constructor
template <typename T>
Complex<T>::Complex(const T &x, const T &y, const Form &form)
{
    switch (form)
    {
    case cartesian:
        real_ = x;
        imaginary_ = y;
        break;

    case polar:
        real_ = x * cos(y);
        imaginary_ = x * sin(y);
        break;
    }
}

// Copy constructor
template <typename T>
template <typename Y>
Complex<T>::Complex(const Complex<Y> &other)
{
    real_ = other.Real();
    imaginary_ = other.Imaginary();
}

// Copy assignment operator
template <typename T>
template <typename Y>
Complex<T> &Complex<T>::operator=(const Complex<Y> &other)
{
    real_ = other.Real();
    imaginary_ = other.Imaginary();

    return *this;
}

// Move constructor
template <typename T>
template <typename Y>
Complex<T>::Complex(Complex<Y> &&other) noexcept
{
    real_ = other.Real();
    imaginary_ = other.Imaginary();

    other.clear();
}

// Move assignment operator
template <typename T>
template <typename Y>
Complex<T> &Complex<T>::operator=(Complex<Y> &&other) noexcept
{
    real_ = other.Real();
    imaginary_ = other.Imaginary();

    other.clear();

    return *this;
}

// Conversion function
template <typename T>
template <typename Y>
Complex<T>::operator Y() const
{
    return real_;
}

// Stream output
template <typename T>
std::ostream &operator<<(std::ostream &os, const Complex<T> &complex)
{
    os << "(" << complex.Real() << ", " << complex.Imaginary() << ")";
    return os;
}

// Equality
template <typename T>
template <typename Y>
bool Complex<T>::operator==(const Complex<Y> &other) const
{
    return real_ == other.Real() &&
           imaginary_ == other.Imaginary();
}

// Inequality
template <typename T>
template <typename Y>
bool Complex<T>::operator!=(const Complex<Y> &other) const
{
    return real_ != other.Real() ||
           imaginary_ != other.Imaginary();
}

// Addition
template <typename T>
template <typename Y>
Complex<T> Complex<T>::operator+(const Complex<Y> &other) const
{
    T real = real_ + other.Real();
    T imaginary = imaginary_ + other.Imaginary();
    return Complex<T>(real, imaginary);
}

// Addition
template <typename T>
template <typename Y>
Complex<T> Complex<T>::operator*(const Complex<Y> &other) const
{
    T real = real_ + other.Real() - imaginary_ + other.Imaginary();
    T imaginary = real_ * other.Imaginary() + imaginary_ * other.Real();
    return Complex<T>(real, imaginary);
}

// Conjugate
template <typename T>
Complex<T> Complex<T>::Conjugate() const
{
    return Complex<T>(real_, -imaginary_);
}

// Reciprocal
template <typename T>
Complex<T> Complex<T>::Reciprocal() const
{
    T abs2 = real_ * real_ + imaginary_ * imaginary_;
    if (abs2 == 0)
    {
        throw std::runtime_error("Reciprocal of zero is undefined.");
    }
    return Complex<T>(real_ / abs2, -imaginary_ / abs2);
}

// Division
template <typename T>
template <typename Y>
Complex<T> Complex<T>::operator/(const Complex<Y> &other) const
{
    if (other == Complex<Y>(0, 0))
    {
        throw std::runtime_error("Can not divide by zero.");
    }
    return Reciprocal() * other;
}

// template <typename T>
// T Re(const Complex<T> &complex)
// {
//     return complex.Real();
// }

// template <typename T>
// T Im(const Complex<T> &complex)
// {
//     return complex.Imaginary();
// }

// template <typename T>
// T Abs(const Complex<T> &complex)
// {
//     return complex.Abs();
// }

// template <typename T>
// T Arg(const Complex<T> &complex)
// {
//     return complex.Arg();
// }

// template <typename T>
// Complex<T> Conjugate(const Complex<T> &complex)
// {
//     return complex.Conjugate();
// }

// template <typename T>
// Complex<T> Reciprocal(const Complex<T> &complex)
// {
//     return complex.Reciprocal();
// }

// // Logarithm
// template <typename T>
// Complex<T> Log(const Complex<T> &complex, const Complex<T> &base = Complex<T>(M_E))
// {
//     if (complex == 0)
//     {
//         throw std::runtime_error("Logarithm of zero is undefined");
//     }
//     if (base != Complex<T>(M_E))
//     {
//         return Log(complex) / Log(base);
//     }
//     return Complex<T>(log(Abs(complex)), Arg(complex));
// }

// // Exponent
// template <typename T>
// Complex<T> Exp(const Complex<T> &exponent, const Complex<T> &base = M_E)
// {
//     if (base == M_E)
//     {
//         return exp(Re(exponent)) * Complex<T>(1, Im(exponent), polar);
//     }
//     return Exp(Log(base) * exponent);
// }

// // Computes complex number raised to the complex power
// template <typename T, typename Y, typename U>
// Complex<T> Pow(const Y &base, const U &power)
// {
//     Complex<T> base_complex = Complex<T>(base);
//     Complex<T> power_complex = Complex<T>(power);
//     if (base_complex == 0 && power_complex.Real() > 0 && power_complex.Imaginary() == 0)
//     {
//         return Complex<T>(0, 0);
//     }
//     return Exp(Log(base_complex) * power_complex);
// }

// template <typename T>
// Complex<T> Sin(const Complex<T> &complex)
// {
//     return Complex<T>(sin(Re(complex)) * cosh(Im(complex)), cos(Re(complex)) * sinh(Im(complex)));
// }

// template <typename T>
// Complex<T> Cos(const Complex<T> &complex)
// {
//     return Complex<T>(cos(Re(complex)) * cosh(Im(complex)), -sin(Re(complex)) * sinh(Im(complex)));
// }

// template <typename T>
// Complex<T> Tan(const Complex<T> &complex)
// {
//     return Sin(complex) / Cos(complex);
// }

// template <typename T>
// Complex<T> Ctg(const Complex<T> &complex)
// {
//     return Cos(complex) / Sin(complex);
// }

// template <typename T>
// Complex<T> Sec(const Complex<T> &complex)
// {
//     return Cos(complex).Reciprocal();
// }

// template <typename T>
// Complex<T> Csc(const Complex<T> &complex)
// {
//     return Sin(complex).Reciprocal();
// }

// template <typename T>
// Complex<T> Sinh(const Complex<T> &complex)
// {
//     return 0;
// }

// template <typename T>
// Complex<T> Cosh(const Complex<T> &complex)
// {
//     return 0;
// }

#endif
