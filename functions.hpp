#pragma once

#include <string>
#include "Complex.hpp"

namespace functions
{

    class Func
    {
    public:
        std::string type;
        Complex parameter;
        Func *f = NULL;
        Func *g = NULL;

        Func(const std::string _type = "const", const Complex _parameter = 0, Func *_f = NULL, Func *_g = NULL);
        Complex Evaluate(const Complex complex = 0) const;
        Func *Derivative() const;
        ~Func();
    };

    Func::Func(const std::string _type, const Complex _parameter, Func *_f, Func *_g)
    {
        type = _type;
        parameter = _parameter;
        f = _f;
        g = _g;
    }

    // Evaluates function at given point
    Complex Func::Evaluate(const Complex complex) const
    {
        if (type == "const")
        {
            return parameter;
        }

        if (type == "pow")
        {
            return Complex::Pow(complex, parameter);
        }

        if (type == "exp")
        {
            return Complex::Exp(complex);
        }

        if (type == "log")
        {
            return Complex::Log(complex, parameter);
        }

        if (type == "sum")
        {
            return f->Evaluate(complex) + g->Evaluate(complex);
        }

        if (type == "prod")
        {
            return f->Evaluate(complex) * g->Evaluate(complex);
        }

        if (type == "comp")
        {
            return f->Evaluate(g->Evaluate(complex));
        }

        return 0;
    }

    // h(x) = c
    Func *Constant(const Complex _parameter = 0)
    {
        return new Func("const", _parameter);
    }

    // h(x) = x ^ a
    Func *Power(const Complex _parameter = 1)
    {
        if (_parameter == 0)
        {
            return Constant(1);
        }
        return new Func("pow", _parameter);
    }

    // h(x) = a ^ x
    Func *Exponent(const Complex _parameter = M_E)
    {
        if (_parameter == 0)
        {
            std::cout << "Invalid exponent base: (" << _parameter << ") ^ x.\n";
            return NULL;
        }

        if (_parameter == 1)
        {
            return Constant(1);
        }

        return new Func("exp", _parameter);
    }

    // h(x) = log_b(x);
    Func *Logarithm(const Complex _parameter = M_E)
    {
        if (_parameter == 0 || _parameter == 1)
        {
            std::cout << "Invalid logarithm base: log_(" << _parameter << ")(x).\n";
            return NULL;
        }

        return new Func("log", _parameter);
    }

    // h(x) = f(x) + h(x)
    Func *Sum(Func *_f, Func *_g)
    {
        if (_f->type == "const" && _f->parameter == 0)
        {
            return _g;
        }

        if (_g->type == "const" && _g->parameter == 0)
        {
            return _f;
        }

        return new Func("sum", 0, _f, _g);
    }

    // h(x) = f(x) * h(x)
    Func *Product(Func *_f, Func *_g)
    {
        if (_f->type == "const" && _f->parameter == 0)
        {
            return _f;
        }

        if (_g->type == "const" && _g->parameter == 0)
        {
            return _g;
        }

        if (_f->type == "const" && _f->parameter == 1)
        {
            return _g;
        }

        if (_g->type == "const" && _g->parameter == 1)
        {
            return _f;
        }

        return new Func("prod", 0, _f, _g);
    }

    // h(x) = f(g(x))
    Func *Composition(Func *_f, Func *_g)
    {
        if (_g->type == "const")
        {
            return Constant(_f->Evaluate(_g->parameter));
        }

        return new Func("comp", 0, _f, _g);
    }

    // h(x) = f(x) - g(x)
    Func *Difference(Func *_f, Func *_g)
    {
        return Sum(_f, Product(Constant(-1), _g));
    }

    // h(x) = f(x) / g(x)
    Func *Division(Func *_f, Func *_g)
    {
        return Product(_f, Composition(Power(-1), _g));
    }

    // h(x) = - f(x)
    Func *Negative(Func *_f)
    {
        return Product(Constant(-1), _f);
    }

    // h(x) = g(x) ^ 2
    Func *Power(Func *_g, const Complex _parameter = 2)
    {
        return Composition(Power(_parameter), _g);
    }

    // h(x) = e ^ g(x)
    Func *Exponent(Func *_g)
    {
        return Composition(Exponent(), _g);
    }

    // h(x) = a ^ g(x)
    Func *Exponent(const Complex _parameter, Func *_g)
    {
        return Composition(Exponent(), Product(Logarithm(_parameter), _g));
    }

    // h(x) = log_b(g(x))
    Func *Logarithm(Func *_g, const Complex _parameter = M_E)
    {
        return Composition(Logarithm(_parameter), _g);
    }

    // Returns the derivative of a given function
    Func *Func::Derivative() const
    {
        // c' = 0
        if (type == "const")
        {
            return Constant();
        }

        // (x ^ n)' = a * x ^ (a - 1)
        if (type == "pow")
        {
            return Product(Constant(parameter), Power(parameter - 1));
        }

        // (a ^ x)' = ln(a) * a ^ x
        if (type == "exp")
        {
            if (parameter != M_E)
            {
                return Product(Constant(Complex::Log(parameter)), Exponent(parameter));
            }

            return Exponent();
        }

        // Log_b(x)' = 1 / (x * Ln(b))
        if (type == "log")
        {
            if (parameter != M_E)
            {
                return Product(Constant(1 / Complex::Log(parameter)), Power(-1));
            }

            return Power(-1);
        }

        // (f(x) + g(x))' = f'(x) + g'(x)
        if (type == "sum")
        {
            return Sum(f->Derivative(), g->Derivative());
        }

        // (f(x) * g(x))' = f'(x) * g(x) + f(x) * g'(x)
        if (type == "prod")
        {
            return Sum(Product(f->Derivative(), g), Product(f, g->Derivative()));
        }

        // f(g(x))' = f'(g(x)) * g'(x)
        if (type == "comp")
        {
            return Product(Composition(f->Derivative(), g), g->Derivative());
        }

        return NULL;
    }

    Func::~Func()
    {
        if (f != NULL)
        {
            f->~Func();
        }
        if (g != NULL)
        {
            g->~Func();
        }
        if (f == NULL && g == NULL)
        {
            delete this;
        }
    }

    typedef Func *Function;

}
