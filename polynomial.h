#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#define SIZE 256

template <typename T>
class polynomial
{
private:
    T coefficients[SIZE];

public:
    polynomial(const T &coefficient = 0)
    {
        coefficients[0] = coefficient;
        for (int i = 1; i < SIZE; i++)
        {
            coefficients[i] = 0;
        }
    }

    polynomial(const polynomial &);

    ~polynomial();

    // polynomial<T> operator+(const polynomial<T> &other);
    // polynomial<T> operator*(const T &coefficient);
    // polynomial<T> operator*(const polynomial<T> &other);
    // friend polynomial<T> operator*(const T &coefficient, const polynomial<T> &other);
};

#endif