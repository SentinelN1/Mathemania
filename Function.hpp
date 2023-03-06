#pragma once

#include "Complex.hpp"

namespace function {
    enum Types {
        constant,
        linear,
        power,
        polynomial,
        rational,
        exponential,
        logarithmic,
        sum,
        product,
        composition
    };

    template<typename T = double>
    class Function {
    private:
        T parameter;
        Types functionType;
        const Function *first;
        const Function *second;

    public:
        Function(const T &param, const Types &type, const Function &f, const Function &g) {
            parameter = param;
            functionType = type;
            first = f;
            second = g;
        }

        Function(const T &constant = 0, const Types &type = Types::constant) {
            parameter = constant;
            functionType = type;
            first = nullptr;
            second = nullptr;
        }

        static Function Sum(const Function &f, const Function &g) {
            return Function(0, sum, f, g);
        }

        static Function Product(const Function &f, const Function &g) {
            return Function(0, product, f, g);
        }

        static Function Composition(const Function &f, const Function &g) {
            return Function(0, composition, f, g);
        }

        static Function Constant(const T &constant) {
            return Function(constant, Types::constant, nullptr, nullptr);
        }

        static Function Power(const T &power) {
            if (power == 0) {
                return Constant(1);
            }
            return Function(power, Types::power, nullptr, nullptr);
        }

        static Function Exponent(const T &base = M_E) {
            if (base == 1) {
                return Constant(1);
            }
            return Function(base, exponential, NULL, NULL);
        }

        static Function Logarithm(const T &base = M_E) {
            return Function(base, logarithmic, NULL, NULL);
        }

        // friend std::ostream &operator<<(std::ostream &os, const Function &f)
        // {
        //     switch (f.functionType)
        //     {
        //     case 'c':
        //         os << f.parameter;
        //         return os;

        //     case 'p':
        //         os << "x";
        //         if (f.parameter != 1)
        //         {
        //             os << "^(" << f.parameter << ")";
        //         }
        //         return os;

        //     case 'e':
        //         if (f.parameter == M_E)
        //         {
        //             os << "e";
        //         }
        //         else
        //         {
        //             os << f.parameter;
        //         }
        //         os << "^x";
        //         return os;

        //     case 'l':
        //         if (f.parameter == M_E)
        //         {
        //             os << "ln";
        //         }
        //         else
        //         {
        //             os << "log{" << f.parameter << "}";
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
                    return parameter;

                case power:
                    return complex::Pow(number, parameter);

                case exponential:
                    return complex::Exp(number, parameter);

                case logarithmic:
                    return complex::Log(number, parameter);

                case sum:
                    return first->Evaluate(number) + second->Evaluate(number);

                case product:
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