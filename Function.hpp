#pragma once

#include "Complex.hpp"

namespace function
{
    enum Types
    {
        constant, // f(z) = C
        power,    // f(z) = z^c
        // polinomial
        exponential,    // f(z) = e^z, a^z
        logarithmic,    // f(z) = ln(z), log_b(z, b)
        summation,      // f(z) = g(z) + h(z)
        multiplication, // f(z) = g(z) * h(z)
        composition,    // f(z) = g(h(z))
        tetration,      // f(z) = g(z)^h(z)
        trigonometric,  // f(z) = sin(z), cos(z), tan(z) / tg(z), cot(z) / ctg(z), sec(z), csc(z)
        hyperbolic      // f(z) = sinh(z), cosh(z), tanh(z), coth(z), sech(z), csch(z)
    };

    template <typename T>
    class Function
    {
    private:
        T parameter_;
        Types type_;
        const Function *firstFunction_;
        const Function *secondFunction_;

    public:
        // Function parameter
        T Parameter() const
        {
            return parameter_;
        }

        // Type of a function
        Types Type() const
        {
            return type_;
        }

        // Default Constructor
        Function(const T &parameter = 0, const Types &type = Types::constant)
        {
            parameter_ = parameter;
            type_ = type;
        }

        // Constructor
        Function(const T &parameter, const Types &type, const Function &firstFunction, const Function &secondFunction)
        {
            parameter_ = parameter;
            type_ = type;
            firstFunction_ = &firstFunction;
            secondFunction_ = &secondFunction;
        }

        // friend std::ostream &operator<<(std::ostream &os, const Function &f)
        // {
        //     switch (f.functionType)
        //     {
        //     case 'c':
        //         os << f.functionParameter;
        //         return os;
        //
        //     case 'p':
        //         os << "x";
        //         if (f.functionParameter != 1)
        //         {
        //             os << "^(" << f.functionParameter << ")";
        //         }
        //         return os;
        //
        //     case 'e':
        //         if (f.functionParameter == M_E)
        //         {
        //             os << "e";
        //         }
        //         else
        //         {
        //             os << f.functionParameter;
        //         }
        //         os << "^x";
        //         return os;
        //
        //     case 'l':
        //         if (f.functionParameter == M_E)
        //         {
        //             os << "ln";
        //         }
        //         else
        //         {
        //             os << "log{" << f.functionParameter << "}";
        //         }
        //         os << "(x)";
        //         return os;
        //
        //     case '+':
        //         os << *f.first << "+" << *f.second;
        //         return os;
        //
        //     case '*':
        //         os << *f.first << "*" << *f.second;
        //         return os;
        //
        //     case 'o':
        //         os << *f.first << "(" << *f.second << ")";
        //         return os;
        //
        //     default:
        //         return os;
        //     }
        // }

        // Function evaluation method
        T Evaluate(const T &value) const
        {
            switch (type_)
            {
            case constant:
                return parameter_;

            case power:
                return complex::Pow(value, parameter_);

            case exponential:
                return complex::Exp(value, parameter_);

            case logarithmic:
                return complex::Log(value, parameter_);

            case summation:
                return firstFunction_->Evaluate(value) + secondFunction_->Evaluate(value);

            case multiplication:
                return firstFunction_->Evaluate(value) * secondFunction_->Evaluate(value);

            case composition:
                return firstFunction_->Evaluate(secondFunction_->Evaluate(value));

            case tetration:
                return complex::Pow(firstFunction_->Evaluate(value), secondFunction_->Evaluate(value));

            default:
                return 0;
            }
        }

        static Function Constant(const T &constant)
        {
            return Function(constant, Types::constant);
        }

        static Function Power(const T &power)
        {
            if (power == 0)
            {
                return Constant(1);
            }
            return Function(power, Types::power);
        }

        static Function Exponent(const T &base = M_E)
        {
            if (base == 0)
            {
                return Constant(0);
            }
            if (base == 1)
            {
                return Constant(1);
            }
            return Function(base, exponential);
        }

        static Function Logarithm(const T &base = M_E)
        {
            return Function(base, logarithmic);
        }

        static Function Summation(const Function &function1, const Function &function2)
        {
            return Function(0, summation, &function1, &function2);
        }

        static Function Multiplication(const Function &function1, const Function &function2)
        {
            return Function(0, multiplication, &function1, &function2);
        }

        static Function Composition(const Function &function1, const Function &function2)
        {
            if (function1.type_ == constant)
            {
                return Constant(function1.parameter_);
            }

            if (function2.type_ == constant)
            {
                return Constant(function1.Evaluate(function2.parameter_));
            }

            if (function1.type_ == power && function1.parameter_ == 1)
            {
                return function2;
            }

            if (function2.type_ == power && function2.parameter_ == 1)
            {
                return function1;
            }

            return Function(0, composition, &function1, &function2);
        }

        // Operators overloading
        Function operator+(const Function &function) const
        {
            return Summation(*this, function);
        }

        Function operator*(const Function &function) const
        {
            return Multiplication(*this, function);
        }

        Function operator*(const T &coefficient) const
        {
            return Multiplication(Constant(coefficient), *this);
        }

        friend Function operator*(const T &coefficient, const Function &function)
        {
            return Multiplication(Constant(coefficient), function);
        }

        Function operator-(const Function &function) const
        {
            return Summation(Multiplication(Constant(-1), function), *this);
        }

        Function operator()(const Function &function) const
        {
            return Composition(*this, function);
        }

        Function Derivative() const
        {
            switch (type_)
            {
            case constant:
                return Constant(0);

            case power:
                if (parameter_ == 1)
                {
                    return Constant(1);
                }
                return Multiplication(Constant(parameter_), Power(parameter_ - 1));

            case exponential:
                return Multiplication(Constant(Log(parameter_)), *this);

            case logarithmic:
                if (parameter_ == M_E)
                {
                    return Power(-1);
                }

            case summation:
                return Summation(firstFunction_->Derivative(), secondFunction_->Derivative());

            case multiplication:
                return Summation(Multiplication(firstFunction_->Derivative(), *secondFunction_), Multiplication(*firstFunction_, secondFunction_->Derivative()));

            case composition:
                return Multiplication(Composition(firstFunction_->Derivative(), *secondFunction_), *secondFunction_);

                // case tetration:
                //     return complex::Pow(firstFunction_->Evaluate(value), secondFunction_->Evaluate(value));
            }
        };
    };
}
