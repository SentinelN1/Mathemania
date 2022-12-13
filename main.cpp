#include <complex>
#include <iostream>
#include "matrix.h"

using std::cin;
using std::complex;
using std::cout;
using std::endl;

int main()
{
    Matrix<double> m = {{1, 3}, {-2, 0}};
    int i = 2;
    m = 2 * m;
    cout << 2 * m << endl;
    return 0;
}
