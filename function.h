#pragma once

#ifndef _FUNCTION
#define _FUNCTION

#include "complex.h"

class function
{
private:
    complex coefficient;
    char type;
    const function *left;
    const function *right;

public:
    function(const complex &_coefficient = 0, const char &_type = 'c', const function *f = NULL, const function *g = NULL)
    {
        coefficient = _coefficient;
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
        return function(_power, 'p');
    }

    static function Exponent(const complex &_exponent)
    {
        return function(_exponent, 'e');
    }

    static function Logarithm(const complex &_logarithm)
    {
        return function(_logarithm, 'l');
    }
};

#endif
