#include <complex>
#include <iostream>
#include "matrix.h"

using std::cin;
using std::complex;
using std::cout;
using std::endl;

int main()
{
    Matrix<double> J = {{2, 1, 0}, {0, 2, 0}, {0, 0, -1}};
    Matrix<double> I = Matrix<double>::Identity(3);
    cout << I.Inverse() << endl;
    cout << I.Inverse() * I << endl;
    cout << I * I.Inverse() << endl;
    return 0;
}
