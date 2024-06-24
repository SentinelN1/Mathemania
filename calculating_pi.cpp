#include <iostream>
#include <cmath>

double Pi(const int &n)
{
    double result = -3.0 * sqrt(3) / 2.0 + 6;

    double interm_term = 0.5;
    for (int k = 0; k <= n; k++)
    {
        interm_term *= (0.5 - k) / (k + 1.0);
        interm_term *= -0.25 * (2.0 * k + 1.0) / (2.0 * k + 3.0);
        result += 12 * interm_term;
        std::cout << "k = " << k << " : " << interm_term << ",\t" << result << "\n";
    }

    return result;
}

int main()
{
    std::cout << Pi(20);

    return 0;
}