#pragma once

#include "complex.h"

class function
{
private:
    complex parameter;
    char type;
    const function *argument;
    const function *left;
    const function *right;

public:
    function(const complex &_parameter, const char &_type, const function *f, const function *g)
    {
        parameter = _parameter;
        type = _type;
        left = f;
        right = g;
    }

    function(const complex &_constant)
    {
        parameter = _constant;
        type = 'c';
        left = NULL;
        right = NULL;
    }

    function(const double &_constant)
    {
        parameter = _constant;
        type = 'c';
        left = NULL;
        right = NULL;
    }

    static function Sum(const function &f, const function &g)
    {
        return function(0, '+', &f, &g);
    }

    static function Product(const function &f, const function &g)
    {
        return function(0, '*', &f, &g);
    }

    static function Composition(const function &f, const function &g)
    {
        return function(0, 'o', &f, &g);
    }

    static function Constant(const complex &_constant)
    {
        return function(_constant, 'c', NULL, NULL);
    }

    static function Power(const complex &_power)
    {
        if (_power != 0)
        {
            return function(_power, 'p', NULL, NULL);
        }
        return Constant(1);
    }

    static function Exponent(const complex &_base = M_E)
    {
        return function(_base, 'e', NULL, NULL);
    }

    static function Logarithm(const complex &_base = M_E)
    {
        return function(_base, 'l', NULL, NULL);
    }

    // friend std::ostream &operator<<(std::ostream &os, const function &f)
    // {
    //     switch (f.type)
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
    //         os << *f.left << "+" << *f.right;
    //         return os;

    //     case '*':
    //         os << *f.left << "*" << *f.right;
    //         return os;

    //     case 'o':
    //         os << *f.left << "(" << *f.right << ")";
    //         return os;

    //     default:
    //         return os;
    //     }
    // }

    complex Evaluate(const complex &number) const
    {
        switch (type)
        {
        case 'c':
            return parameter;

        case 'p':
            return complex::Pow(number, parameter);

        case 'e':
            return complex::Exp(number, parameter);

        case 'l':
            return complex::Log(number, parameter);

        case '+':
            return left->Evaluate(number) + right->Evaluate(number);

        case '*':
            return left->Evaluate(number) * right->Evaluate(number);

        case 'o':
            return left->Evaluate(right->Evaluate(number));

        default:
            return 0;
        }
    }

    function operator+(const function &f)
    {
        return function(0, '+', this, &f);
    }

    function operator*(const function &f)
    {
        return function(0, '*', this, &f);
    }

    function operator()(const function &f)
    {
        return function(0, 'o', this, &f);
    }

    friend function operator*(const complex &_coefficient, const function &_function)
    {
        return function::Constant(_coefficient) * _function;
    }
};
