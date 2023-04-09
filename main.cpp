#include <iostream>
#include "Complex.hpp"
#include "Function.hpp"

using namespace complex;
using namespace function;

int main()
{
    Function<Complex<double>> f = Function<Complex<double>>::Constant(Complex<double>(6, 4));
    std::cout << f.Derivative().Parameter();
}
