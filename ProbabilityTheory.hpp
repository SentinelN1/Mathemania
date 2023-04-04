#pragma once

#include <vector>
#include <list>
#include <set>
#include <map>

template <typename T>
class DiscreteRandomVariable
{
private:
    std::map<T, double> probabilities;

public:
    void Probabilities() const
    {
        for (auto i : probabilities)
        {
            std::cout << i.first << " : " << i.second << "\n";
        }
    }

    DiscreteRandomVariable() = default;

    DiscreteRandomVariable(const std::vector<T> &prob)
    {
        for (auto i : prob)
        {
            probabilities[i] = 1.0 / prob.size();
        }
    }

    DiscreteRandomVariable(const std::list<T> &prob)
    {
        for (auto i : prob)
        {
            probabilities[i] = 1.0 / prob.size();
        }
    }

    DiscreteRandomVariable(const std::set<T> &prob)
    {
        for (auto i : prob)
        {
            probabilities[i] = 1.0 / prob.size;
        }
    }

    DiscreteRandomVariable(const std::map<T, double> &prob)
    {
        probabilities = prob;
    }

    double ExpectedValue() const
    {
        double expectedValue = 0;
        for (auto i : probabilities)
        {
            expectedValue += i.first * i.second;
        }
        return expectedValue;
    }

    double Variance() const
    {
        double expetedValue = ExpectedValue();
        double variance = 0;
        for (auto i : probabilities)
        {
            variance += i.first * i.first * i.second;
        }
        return variance - expetedValue * expetedValue;
    }

    DiscreteRandomVariable operator+(const DiscreteRandomVariable &other) const
    {
        DiscreteRandomVariable result;
        for (auto i : probabilities)
        {
            for (auto j : other.probabilities)
            {
                result.probabilities[i.first + j.first] += i.second * j.second;
            }
        }
    }
};
