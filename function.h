#ifndef MATHEMANIA_FUNCTION_H_
#define MATHEMANIA_FUNCTION_H_

enum Types
{
    constant,       // f(z) = C
    power,          // f(z) = z^c
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

    // Default constructor
    Function<T>();

    // Default constructor
    Function<T>(const T &parameter, const Types &type)
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

    // Function evaluation method
    T Evaluate(const T &value) const
    {
        switch (type_)
        {
        case constant:
            return parameter_;

        case power:
            return std::pow(value, parameter_);

        case exponential:
            return std::exp(value, parameter_);

        case logarithmic:
            return std::log(value, parameter_);

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
        return {base, logarithmic};
    }

    static Function Summation(const Function &function1, const Function &function2)
    {
        return {0, summation, &function1, &function2};
    }

    static Function Multiplication(const Function &function1, const Function &function2)
    {
        return {0, multiplication, &function1, &function2};
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

#endif
