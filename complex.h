#ifndef MATHEMANIA_COMPLEX_H_
#define MATHEMANIA_COMPLEX_H_

#include <iostream>

enum Form
{
    cartesian,
    polar
};

template <typename T>
class Complex
{
private:
    T real_, imaginary_;

public:
    void clear();

    T Real() const;      // Real part of a complex number
    T Imaginary() const; // Imaginary part of a complex number

    T Abs() const; // Absolute value of a complex number
    T Arg() const; // Argument of a complex number

    bool IsPurelyReal() const;      // Is a number purely real?
    bool IsPurelyImaginary() const; // Is a number purely imaginary?

    explicit Complex(const T & = T(),
                     const T & = T(),
                     const Form & = cartesian); // Constructor

    template <typename Y>
    Complex(const Complex<Y> &); // Copy constructor

    template <typename Y>
    Complex<T> &operator=(const Complex<Y> &); // Copy assignment operator

    template <typename Y>
    Complex(Complex<Y> &&) noexcept; // Move constructor

    template <typename Y>
    Complex<T> &operator=(Complex<Y> &&) noexcept; // Move assignment operator

    template <typename Y>
    operator Y() const; // Conversion function

    template <typename Y>
    friend std::ostream &operator<<(std::ostream &, const Complex<Y> &); // Stream output

    template <typename Y>
    bool operator==(const Complex<Y> &) const; // Equality

    template <typename Y>
    bool operator!=(const Complex<Y> &) const; // Inequality

    Complex<T> operator+() const; // Unary plus

    template <typename Y>
    Complex<T> operator+(const Complex<Y> &) const; // Addition

    template <typename Y>
    Complex<T> &operator+=(const Complex<Y> &); // Increment

    Complex<T> operator-() const; // Unary minus

    template <typename Y>
    Complex<T> operator-(const Complex<Y> &) const; // Subtraction

    template <typename Y>
    Complex<T> &operator-=(const Complex<Y> &); // Decrement

    template <typename Y>
    Complex<T> operator*(const Complex<Y> &) const; // Multiplication

    template <typename Y>
    Complex<T> &operator*=(const Complex<Y> &);

    Complex<T> Conjugate() const; // Conjugate

    Complex<T> Reciprocal() const; // Reciprocal

    template <typename Y>
    Complex<T> operator/(const Complex<Y> &) const; // Division

    template <typename Y>
    Complex<T> &operator/=(const Complex<Y> &);
};

#endif
