#include <iostream>
#include "Complex.hpp"

using std::cin;
using std::cout;
using std::endl;
using namespace complex;

int main() {
    Complex<float> i(0, -1);
    cout << Exp(i * M_PI) << endl;
}
