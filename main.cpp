#include <iostream>
#include <vector>
#include "ProbabilityTheory.hpp"

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    DiscreteRandomVariable<int> d(v);
    std::cout << d.ExpectedValue() << " " << d.Variance() << "\n";
}
