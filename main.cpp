#include <iostream>
#include <vector>
#include "ProbabilityTheory.hpp"

int main()
{
    // std::vector<int> vector = {-1, 1};
    DiscreteRandomVariable<double> coin({-0.5, 0.5});
    auto total = coin + coin + coin + coin + coin + coin + coin + coin + coin + coin + coin + coin + coin + coin + coin + coin;
    std::cout << "Expected value: " << total.ExpectedValue() << "\n";
    std::cout << "Variance: " << total.Variance() << "\n";
    total.Probabilities();
}
