#include <stdio.h>
#include <math.h>

double nth_root(double value)
{
}

double square_root(double square, const double epsilon, unsigned long long int max_iterations)
{
    if (square < 0)
    {
        // No real solution
        return -1;
    }

    double root = square;

    unsigned long long int iteration = 0;
    while (iteration < max_iterations && fabs(root * root - square) > epsilon)
    {
        iteration++;
        root -= (root * root - square) / (2 * root);
    }

    return root;
}

double calculate_e(double epsilon)
{
    double result = 0;
    double term = 1;

    result += term;
    unsigned int n = 1;
    while (fabs(term) > epsilon)
    {
        term /= n;
        result += term;
        n++;
    }

    return result;
}

long double calculate_pi(const unsigned long long int number_of_iterations)
{
    long double result = 0;
    long double term = 0.5;

    result += term;
    for (unsigned long long int k = 1; k <= number_of_iterations; k++)
    {
        term *= (0.5 - k + 1) / k * (-1) * (2 * k - 1) / (2 * k + 1) / 4;
        result += term;
    }

    result = 12 * result - 3 * sqrt(3) / 2;
    return result;
}


double calculate_pi_2(int number_of_iterations)
{
    double result = 0;

    for (int k = 0; k <= number_of_iterations; k++)
    {
        double term = 1.0 / (2 * k + 1);
        if (k % 2 == 1)
        {
            term *= -1;
        }
        result += term;
    }

    return 4 * result;
}

double calculate_pi_3(int number_of_iterations)
{
    double result = 0;

    for (int n = 1; n <= number_of_iterations; n++)
    {
        result += 1.0 / (n * n);
    }

    return sqrt(6 * result);
}

int main()
{   
    // long double PI = calculate_pi(__SIZE_MAX__);
    double PI = calculate_pi(1e9);
    printf("%.20lf", PI);
    return 0;
}
