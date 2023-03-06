#include <iostream>
#include "Complex.hpp"

using std::cin;
using std::cout;
using std::endl;
using namespace complex;

int main() {
    Complex<float> c(-1, 1);
    cout << c * 2 << endl;
    cout << 2 * c << endl;
}
