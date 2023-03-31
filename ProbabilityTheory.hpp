#pragma once
#include <list>

double ExpectedValue(const std::list<std::pair<double, double>> &randomVariable)
{
    double expectedValue = 0;
    for (auto pair : randomVariable)
    {
        expectedValue += pair.first * pair.second;
    }
    return expectedValue;
}

double Variance(const std::list<std::pair<double, double>> &randomVariable)
{
    double expectedValue = ExpectedValue(randomVariable);
    double variance = 0;
    for (auto pair : randomVariable)
    {
        variance += pair.first * pair.first * pair.second;
    }
    return variance - expectedValue * expectedValue;
}
