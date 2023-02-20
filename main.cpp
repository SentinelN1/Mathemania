#include "matrix.h"

int main()
{
    Matrix<double> v1 = {1, 0};
    Matrix<double> v2 = {1, 0};
    Matrix<double> A = {{2, 0},
                        {0, 0.5}};
    std::cout << v2.Transpose() * A * v1;
}
