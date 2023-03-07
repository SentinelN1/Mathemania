#pragma once

#include "Complex.hpp"

namespace function {
    enum Types {
        constant,
        power,
        exponential,
        logarithmic,
        summation,
        multiplication,
        composition,
        tetration
    };

    template<typename T = complex::Complex<double>>
    class Function {
    private:
        T functionParameter;
        Types functionType;
        const Function *first;
        const Function *second;

    public:
        T Parameter() const {
            return functionParameter;
        }

        Types Type() const {
            return functionType;
        }

        Function(const T &parameter = 0, const Types &type = constant) {
            functionParameter = parameter;
            functionType = type;
            first = nullptr;
            second = nullptr;
        }

        Function(const T &parameter, const Types &type, const Function &f, const Function &g) {
            functionParameter = parameter;
            functionType = type;
            first = &f;
            second = &g;
        }

        static Function Constant(const T &constant) {
            return Function(constant, Types::constant);
        }

        static Function Power(const T &power) {
            if (power == 0) {
                return Constant(1);
            }
            return Function(power, Types::power);
        }

        static Function Exponent(const T &base = M_E) {
            if (base == 1) {
                return Constant(1);
            }
            return Function(base, exponential);
        }

        static Function Logarithm(const T &base = M_E) {
            return Function(base, logarithmic);
        }

        static Function Summation(const Function &f, const Function &g) {
            return Function(0, summation, f, g);
        }

        static Function Multiplication(const Function &f, const Function &g) {
            return Function(0, multiplication, f, g);
        }

        static Function Composition(const Function f, const Function g) {
            if (g.functionType == constant) {
                return Constant(f.Evaluate(g.functionParameter));
            }
            if (g.functionType == power && g.functionParameter == 1) {
                return f;
            }

            return Function(0, composition, f, g);
        }


        // friend std::ostream &operator<<(std::ostream &os, const Function &f)
        // {
        //     switch (f.functionType)
        //     {
        //     case 'c':
        //         os << f.functionParameter;
        //         return os;

        //     case 'p':
        //         os << "x";
        //         if (f.functionParameter != 1)
        //         {
        //             os << "^(" << f.functionParameter << ")";
        //         }
        //         return os;

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

        //     case '+':
        //         os << *f.first << "+" << *f.second;
        //         return os;

        //     case '*':
        //         os << *f.first << "*" << *f.second;
        //         return os;

        //     case 'o':
        //         os << *f.first << "(" << *f.second << ")";
        //         return os;

        //     default:
        //         return os;
        //     }
        // }

        T Evaluate(const T &number) const {
            switch (functionType) {
                case constant:
                    return functionParameter;

                case power:
                    return complex::Pow(number, functionParameter);

                case exponential:
                    return complex::Exp(number, functionParameter);

                case logarithmic:
                    return complex::Log(number, functionParameter);

                case summation:
                    return first->Evaluate(number) + second->Evaluate(number);

                case multiplication:
                    return first->Evaluate(number) * second->Evaluate(number);

                case composition:
                    return first->Evaluate(second->Evaluate(number));

                default:
                    return 0;
            }
        }

//        Function operator+(const Function &f) {
//            return Function(0, '+', this, &f);
//        }
//
//        Function operator*(const Function &f) {
//            return Function(0, '*', this, &f);
//        }
//
//        Function operator()(const Function &f) {
//            return Function(0, 'o', this, &f);
//        }
//
//        friend Function operator*(const T &_coefficient, const Function &_function) {
//            return Function::Constant(_coefficient) * _function;
//        }
    };
}