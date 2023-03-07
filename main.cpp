#include <iostream>
#include "Function.hpp"

using std::cin;
using std::cout;
using std::endl;
using namespace complex;
using namespace function;

int main() {
    auto function0 = Function<>::Constant(-11);
    auto function1 = Function<>::Exponent();
    auto function2 = Function<>::Power(1);
    auto function3 = Function<>::Composition(function1, function2);
    cout << function0.Parameter() << endl;
    cout << function1.Parameter() << endl;
    cout << function2.Parameter() << endl;
    cout << function3.Parameter() << endl;
}
