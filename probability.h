#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

typedef float Real;

// class RandomVariable {
//     Real cumulative_distribution_function(Real);

//     RandomVariable(Real CDF(Real)) {
//         cumulative_distribution_function = CDF;
//     }
// }

// class DiscreteRandomVariable : public RandomVariable
class DiscreteRandomVariable
{
private:
    std::map<Real, Real> probability_distribution;

public:
    std::map<Real, Real> Distribution() const
    {
        return probability_distribution;
    }

    DiscreteRandomVariable() = default;

    DiscreteRandomVariable(const std::initializer_list<Real> &values)
    {
        unsigned int size = values.size();
        for (const Real &value : values)
        {
            probability_distribution[value] = 1.0 / size;
        }
    }

    std::map<Real, Real> Normalize(const std::map<Real, Real> &distribution)
    {
        std::map<Real, Real> normalized_distribution;
        Real total_probability = 0;

        for (const auto &[value, probability] : distribution)
        {
            total_probability += probability;
        }

        for (const auto &[value, probability] : distribution)
        {
            normalized_distribution[value] += probability / total_probability;
        }
        return normalized_distribution;
    }

    DiscreteRandomVariable(const std::map<Real, Real> &distribution)
    {
        probability_distribution = Normalize(distribution);
    }

    Real ExpectedValue() const
    {
        Real expected_value = 0;
        for (const auto &[value, probability] : probability_distribution)
        {
            expected_value += value * probability;
        }
        return expected_value;
    }

    Real Variance() const
    {
        Real expetedValue = ExpectedValue();
        Real variance = 0;
        for (const auto &[value, probability] : probability_distribution)
        {
            variance += (value * value) * probability;
        }
        return variance - expetedValue * expetedValue;
    }

    DiscreteRandomVariable operator+(const DiscreteRandomVariable &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[x_value, x_probability] : probability_distribution)
        {
            for (const auto &[y_value, y_probability] : other.probability_distribution)
            {
                result.probability_distribution[x_value + y_value] += x_probability * y_probability;
            }
        }
        return result;
    }

    DiscreteRandomVariable operator+(const Real &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[value, probability] : probability_distribution)
        {
            result.probability_distribution[value + other] += probability;
        }
        return result;
    }

    DiscreteRandomVariable operator*(const DiscreteRandomVariable &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[x_value, x_probability] : probability_distribution)
        {
            for (const auto &[y_value, y_probability] : other.probability_distribution)
            {
                result.probability_distribution[x_value * y_value] += x_probability * y_probability;
            }
        }
        return result;
    }

    DiscreteRandomVariable operator*(const Real &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[value, probability] : probability_distribution)
        {
            result.probability_distribution[value * other] += probability;
        }
        return result;
    }

    DiscreteRandomVariable operator-(const Real &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[value, probability] : probability_distribution)
        {
            result.probability_distribution[value - other] += probability;
        }
        return result;
    }

    DiscreteRandomVariable operator-(const DiscreteRandomVariable &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[x_value, x_probability] : probability_distribution)
        {
            for (const auto &[y_value, y_probability] : other.probability_distribution)
            {
                result.probability_distribution[x_value - y_value] += x_probability * y_probability;
            }
        }
        return result;
    }

    DiscreteRandomVariable operator/(const Real &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[value, probability] : probability_distribution)
        {
            result.probability_distribution[value / other] += probability;
        }
        return result;
    }

    DiscreteRandomVariable operator/(const DiscreteRandomVariable &other) const
    {
        DiscreteRandomVariable result;
        for (const auto &[x_value, x_probability] : probability_distribution)
        {
            for (const auto &[y_value, y_probability] : other.probability_distribution)
            {
                result.probability_distribution[x_value / y_value] += x_probability * y_probability;
            }
        }
        return result;
    }

    friend std::ostream &operator<<(std::ostream &os, const DiscreteRandomVariable &X)
    {
        for (const auto &[value, probability] : X.Distribution())
        {
            os << "P(X = " << value << ") = " << probability << "\n";
        }
        return os;
    }
};

Real E(const DiscreteRandomVariable &X)
{
    Real expected_value = 0;
    for (const auto &[value, probability] : X.Distribution())
    {
        expected_value += value * probability;
    }
    return expected_value;
}

Real D(const DiscreteRandomVariable &X)
{
    Real expected_value = 0;
    for (const auto &[value, probability] : X.Distribution())
    {
        expected_value += value * probability;
    }
    return expected_value;
}