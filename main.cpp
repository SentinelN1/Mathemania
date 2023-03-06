#include <iostream>
#include "Function.hpp"
#include "Matrix.hpp"

using std::cin;
using std::cout;
using std::endl;
using namespace complex;
using namespace matrix;
using namespace function;

int main() {
    Function<Complex<float>> f(2, power);
    cout << f.Evaluate(3);
}
