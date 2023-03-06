#pragma once
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>

namespace complex {
    template<typename T = float>
    class Complex {
    private:
        T real, imaginary;

    public:
        enum Form {
            cartesian,
            polar
        };

        // Constructor
        Complex(const T &x = 0, const T &y = 0, Form form = cartesian) {
            switch (form) {
                case cartesian:
                    real = x;
                    imaginary = y;
                    break;
                case polar:
                    real = x * cos(y);
                    imaginary = x * sin(y);
                    break;
            }
        }

        bool IsReal() const {
            return imaginary == 0;
        }

        bool IsImaginary() const {
            return real == 0;
        }

        // Real part of a complex number
        T Real() const {
            return real;
        }

        // Imaginary part of a complex number
        T Imaginary() const {
            return imaginary;
        }

        // Absolute value of a complex number
        T Abs() const {
            return sqrt(real * real + imaginary * imaginary);
        }

        // Argument of a complex number
        T Arg() const {
            return atan2(imaginary, real);
        }

        // Equality operator
        friend bool operator==(const Complex &complex1, const Complex &complex2) {
            return (complex1.real == complex2.real && complex1.imaginary == complex2.imaginary);
        }

        // Inequality operator
        friend bool operator!=(const Complex &complex1, const Complex &complex2) {
            return (complex1.real != complex2.real || complex1.imaginary != complex2.imaginary);
        }

        // Stream output
        friend std::ostream &operator<<(std::ostream &os, const Complex<T> &complex) {
//            if (complex.real != 0) {
//                os << complex.real;
//
//                if (complex.imaginary != 0) {
//                    if (complex.imaginary > 0) {
//                        os << "+";
//                    }
//                    os << complex.imaginary << "i";
//                    return os;
//                }
//
//                os << complex.real;
//                return os;
//            }
//            if (complex.imaginary != 0) {
//                os << complex.imaginary << "i";
//                return os;
//            }
//            os << 0;
            os << "(" << complex.real << "; " << complex.imaginary << ")";
            return os;
        }

        // Unary plus
        Complex operator+() const {
            return Complex(real, imaginary);
        }

        // Unary Minus
        Complex operator-() const {
            return Complex(-real, -imaginary);
        }

        // Addition
        friend Complex operator+(const Complex &complex1, const Complex &complex2) {
            return Complex(complex1.real + complex2.real, complex1.imaginary + complex2.imaginary);
        }

        // Subtraction
        friend Complex operator-(const Complex &complex1, const Complex &complex2) {
            return Complex(complex1.real - complex2.real, complex1.imaginary - complex2.imaginary);
        }

        // Multiplication
        friend Complex operator*(const Complex &complex1, const Complex &complex2) {
            return Complex(complex1.real * complex2.real - complex1.imaginary * complex2.imaginary,
                           complex1.real * complex2.imaginary + complex1.imaginary * complex2.real);
        }

//        // Increment
//        void operator+=(const Complex &complex) {
//            real += complex.real;
//            imaginary += complex.imaginary;
//        }
//
//        // Decrement
//        void operator-=(const Complex &complex) {
//            real -= complex.real;
//            imaginary -= complex.imaginary;
//        }
//
//        void operator*=(const Complex &complex) {
//            *this = *this * complex;
//        }

        // Complex Conjugate
        Complex Conjugate() const {
            return Complex(real, -imaginary);
        }

        // Complex Reciprocal
        Complex Reciprocal() const {
            T abs2 = real * real + imaginary * imaginary;
            if (abs2 != 0) {
                throw std::exception();
            }
            return Complex(real / abs2, -imaginary / abs2);
        }

        // Division operator
        friend Complex operator/(const Complex &complex1, const Complex &complex2) {
            return complex1 * complex2.Reciprocal();
        }

//// Calculates logarithm of a complex number. By default base is set to e (~2.7182)
//        static complex Log(const complex &number, const complex &base = M_E) {
//            if (number != 0) {
//                if (base != M_E) {
//                    return Log(number) / Log(base);
//                }
//
//                return complex(log(Abs(number)), Arg(number));
//            }
//            std::cout << "Log(0) is undefined\n";
//            exit(185); // Replace with exception
//        }
//
//// Raises e to complex power
//        static complex Exp(const complex &exponent, const complex &base = M_E) {
//            if (base == M_E) {
//                return exp(Re(exponent)) * complex(1, Im(exponent), true);
//            }
//            return Exp(Log(base) * exponent);
//        }
//
//// Computes complex number raised to the complex power
//        static complex Pow(const complex &base, const complex &power) {
//            if (base == 0 && Re(power) > 0 && Im(power) == 0) {
//                return 0;
//            }
//            return Exp(Log(base) * power);
//        }
//
//        static complex Sin(const complex &z) {
//            return complex(sin(Re(z)) * cosh(Im(z)), cos(Re(z)) * sinh(Im(z)));
//        }
//
//        static complex Cos(const complex &z) {
//            return complex(cos(Re(z)) * cosh(Im(z)), -sin(Re(z)) * sinh(Im(z)));
//        }
//
//        static complex Tan(const complex &z) {
//            return Sin(z) / Cos(z);
//        }
//
//        Complex Ctg(const Complex &z) {
//            return Cos(z) / Sin(z);
//        }
    };

    template<typename T>
    T Re(const Complex<T> &complex) {
        return complex.Real();
    }

    template<typename T>
    T Im(const Complex<T> &complex) {
        return complex.Imaginary();
    }

    template<typename T>
    T Abs(const Complex<T> &complex) {
        return complex.Abs();
    }

    template<typename T>
    T Arg(const Complex<T> &complex) {
        return complex.Arg();
    }

    template<typename T>
    Complex<T> Conjugate(const Complex<T> &complex) {
        return complex.Conjugate();
    }

    template<typename T>
    Complex<T> Reciprocal(const Complex<T> &complex) {
        return complex.Reciprocal();
    }
}