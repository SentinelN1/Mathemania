#include <iostream>
#include "matrix.h"

// using namespace std;
using namespace linal;

int main()
{
    // Vector2D v = Vector2D(0.8, 0.6);
    // Vector2D u = Vector2D(-0.8, -0.6);

    // std::cout << Vector2D::Dot(v, u) << std::endl;
    // std::cout << Vector2D::Rad(v, u) << std::endl;
    // std::cout << Vector2D::Deg(v, u) << std::endl;

    Vector x({1, 2, 3});
    Vector y({2, 3, 1});
    Vector z = x + y;

    Real res = AngleRad(x, y) * 180.0 / M_PI;
    std::cout << res;
    return 0;
}
