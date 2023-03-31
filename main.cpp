#include <iostream>
#include <list>
// #include "Function.hpp"
#include "ProbabilityTheory.hpp"

using std::cin;
using std::cout;
using std::endl;
// using namespace complex;
// using namespace function;

int main()
{
    // std::list<std::pair<double, double>> dice = {{1, 1.0 / 6}, {2, 1.0 / 6}, {3, 1.0 / 6}, {4, 1.0 / 6}, {5, 1.0 / 6}, {6, 1.0 / 6}};
    std::list<std::pair<double, double>> dice = {{-1, 1.0 / 2}, {1, 1.0 / 2}};

    double expectedValue = ExpectedValue(dice);
    cout << expectedValue << endl;

    double variance = Variance(dice);
    cout << variance << endl;

    // auto function0 = Function<>::Constant(-11);
    // auto function1 = Function<>::Exponent();
    // auto function2 = Function<>::Power(1);
    // auto function3 = Function<>::Composition(function1, function2);
    // cout << function0.Parameter() << endl;
    // cout << function1.Parameter() << endl;
    // cout << function2.Parameter() << endl;
    // cout << function3.Parameter() << endl;
}
