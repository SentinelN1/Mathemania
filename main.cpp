#include <complex>
#include <iostream>
#include "matrix.h"

using std::cin;
using std::complex;
using std::cout;
using std::endl;

int main()
{
    Matrix<double> A = -2.0;
    // Matrix<double> J = {{-2, 1, 0}, {0, -2, 0}, {0, 0, 1}};
    A.Inverse();
    // cout << A.Inverse() << endl;
    return 0;
}
