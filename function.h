#pragma once

#include "complex.h"

class function
{
private:
    complex param;
    char type;
    const function *arg;
    const function *left;
    const function *right;

public:
    function(const complex &_param = 0, const char &_type = 'c', const function *f = NULL, const function *g = NULL)
    {
        param = _param;
        type = _type;
        left = f;
        right = g;
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
        return function(_constant);
    }

    static function Power(const complex &_power)
    {
        if (_power != 0)
        {
            return function(_power, 'p');
        }
        return Constant(1);
    }

    static function Exponent(const complex &_base = M_E)
    {
        return function(_base, 'e');
    }

    static function Logarithm(const complex &_base = M_E)
    {
        return function(_base, 'l');
    }

    friend std::ostream &operator<<(std::ostream &os, const function &f)
    {
        switch (f.type)
        {
        case 'c':
            os << f.param;
            return os;

        case 'p':
            os << "x";
            if (f.param != 1)
            {
                os << "^(" << f.param << ")";
            }
            return os;

        case 'e':
            if (f.param == M_E)
            {
                os << "e";
            }
            else
            {
                os << f.param;
            }
            os << "^x";
            return os;

        case 'l':
            if (f.param == M_E)
            {
                os << "ln";
            }
            else
            {
                os << "log{" << f.param << "}";
            }
            os << "(x)";
            return os;

        case '+':
            os << *f.left << "+" << *f.right;
            return os;

        case '*':
            os << *f.left << "*" << *f.right;
            return os;

        case 'o':
            os << *f.left << "(" << *f.right << ")";
            return os;

        default:
            return os;
        }
    }

    complex Evaluate(const complex &z) const
    {
        switch (type)
        {
        case 'c':
            return param;

        case 'p':
            return complex::Pow(z, param);

        case 'e':
            return complex::Exp(z, param);

        case 'l':
            return complex::Log(z, param);

        case '+':
            return left->Evaluate(z) + right->Evaluate(z);

        case '*':
            return left->Evaluate(z) * right->Evaluate(z);

        case 'o':
            return left->Evaluate(right->Evaluate(z));

        default:
            break;
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
};
