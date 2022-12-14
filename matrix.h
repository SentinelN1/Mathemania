#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

template <typename T>
class Matrix
{
private:
    int rows, columns;
    T *data;

public:
    // Default constructor
    Matrix<T>()
    {
        rows = 0;
        columns = 0;
        data = nullptr;
    }

    // Constructor
    // Creates matrix RxC
    Matrix<T>(const int &r, const int &c = 1)
    {
        rows = r;
        columns = c;
        data = new T[rows * columns];

        // Fills matrix with zeros
        for (int i = 0; i < rows * columns; i++)
        {
            data[i] = 0;
        }
    }

    // Constructor
    // Creates matrix from initializer_list<initializer_list>
    Matrix<T>(std::initializer_list<std::initializer_list<T>> matrix)
    {
        rows = matrix.size();
        columns = (matrix.begin())->size();

        for (auto row : matrix)
        {
            if (row.size() != columns)
            {
                throw std::invalid_argument("Enter rectangular matrix with a constant length of rows.");
            }
        }

        data = new T[rows * columns];
        int index = 0;

        for (auto row : matrix)
        {
            for (auto i : row)
            {
                data[index] = i;
                index++;
            }
        }
    }

    // Constructor
    // Creates matrix from initializer_list
    Matrix<T>(std::initializer_list<T> matrix)
    {
        rows = matrix.size();
        columns = 1;

        data = new T[rows * columns];
        int index = 0;

        for (auto i : matrix)
        {
            data[index] = i;
            index++;
        }
    }

    // Copy constructor
    Matrix<T>(const Matrix<T> &other)
    {
        if (this != &other)
        {
            if (data)
            {
                delete[] data;
            }

            rows = other.rows;
            columns = other.columns;

            data = new T[rows * columns];

            for (int i = 0; i < rows * columns; i++)
            {
                data[i] = other.data[i];
            }
        }
    }

    // Destructor
    ~Matrix<T>()
    {
        if (data)
        {
            delete[] data;
        }
    }

    // operator=
    Matrix<T> &operator=(const Matrix<T> &other)
    {
        if (this == &other)
        {
            return *this;
        }

        if (data)
        {
            delete[] data;
        }

        rows = other.rows;
        columns = other.columns;

        data = new T[rows * columns];

        for (int i = 0; i < rows * columns; i++)
        {
            data[i] = other.data[i];
        }

        return *this;
    }

    // Console output
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows; i++)
        {
            if (i == 0)
            {
                os << std::setw(4) << "{{";
            }
            else
            {

                os << std::setw(4) << "{";
            }

            for (int j = 0; j < matrix.columns; j++)
            {
                os << std::setw(4) << matrix.data[i * matrix.columns + j];
                if (j < matrix.columns - 1)
                {
                    os << ",";
                }
                else
                {
                    os << std::setw(4) << "}";
                }
            }
            if (i < matrix.rows - 1)
            {
                os << std::endl;
            }
            else
            {
                os << "}";
            }
        }
        return os;
    }

    // Input from console
    friend std::istream &operator>>(std::istream &is, Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows * matrix.columns; ++i)
        {
            is >> matrix.data[i];
        }
        return is;
    }

    // Matrix addition
    Matrix<T> operator+(const Matrix<T> &other)
    {
        if (rows != other.rows || columns != other.columns)
        {
            throw std::invalid_argument("Only matrices of equal dimensions can be added together.");
        }

        Matrix<T> matrix(rows, columns);
        for (int i = 0; i < rows * columns; i++)
        {
            matrix.data[i] = data[i] + other.data[i];
        }

        return matrix;
    }

    // Matrix scalar multiplication
    friend Matrix<T> operator*(const T &scalar, const Matrix<T> &other)
    {
        Matrix<T> matrix(other.rows, other.columns);

        for (int i = 0; i < other.rows * other.columns; i++)
        {
            matrix.data[i] = other.data[i] * scalar;
        }

        return matrix;
    }

    // Matrix scalar multiplication
    friend Matrix<T> operator*(const Matrix<T> &other, const T &scalar)
    {
        return scalar * other;
    }

    // Matrix multiplication
    Matrix<T> operator*(const Matrix<T> &other)
    {
        if (columns != other.rows)
        {
            throw std::invalid_argument(
                "Number of columns of the left matrix should be equal to the number of rows of the right matrix.");
        }

        Matrix<T> matrix(rows, other.columns);
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < other.columns; c++)
            {
                T tmp = 0;
                for (int i = 0; i < columns; i++)
                {
                    tmp += data[columns * r + i] * other.data[other.columns * i + c];
                }
                matrix.data[other.columns * r + c] = tmp;
            }
        }

        return matrix;
    }

    // Unary operator-
    Matrix<T> operator-() const
    {
        return -1 * *this;
    }

    // Unary operator+
    Matrix<T> operator+() const
    {
        return *this;
    }

    // Matrix subtraction
    Matrix<T> operator-(const Matrix<T> &other) const
    {
        if (rows != other.rows || columns != other.columns)
        {
            throw std::invalid_argument("Matrices should be of equal dimensions.");
        }
        Matrix<T> matrix(rows, columns);
        for (int i = 0; i < rows * columns; ++i)
        {
            matrix.data[i] = data[i] - other.data[i];
        }
        return matrix;
    }

    // Matrix equality
    bool operator==(const Matrix<T> &other)
    {
        if (rows == other.rows && columns == other.columns)
        {
            bool tmp = true;
            for (int i = 0; i < rows * columns; i++)
            {
                if (data[i] != other.data[i])
                {
                    tmp = false;
                    break;
                }
            }
            return tmp;
        }
        return false;
    }

    // Element of a matrix
    T &operator()(const int &row, const int &column)
    {
        if (row >= rows || column >= columns)
        {
            throw std::invalid_argument("Index out of range.");
        }

        T &tmp = data[row * columns + column];

        return tmp;
    }

    // Identity matrix
    static Matrix<T> Identity(const int &size)
    {
        Matrix<T> matrix(size, size);
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                matrix.data[size * i + j] = 0;
                if (i == j)
                {
                    matrix.data[size * i + j] = 1;
                }
            }
        }
        return matrix;
    }

    Matrix<T> Minor(const int &row, const int &column)
    {
        Matrix<T> matrix(rows - 1, columns - 1);
        for (int i = 0; i < rows - 1; i++)
        {
            for (int j = 0; j < columns - 1; j++)
            {
                int x = i;
                int y = j;
                if (i >= row)
                    x = i + 1;
                if (j >= column)
                    y = j + 1;
                matrix.data[i * (columns - 1) + j] = data[x * columns + y];
            }
        }
        return matrix;
    }

    T Determinant()
    {
        if (rows != columns)
        {
            throw std::invalid_argument("Determinant of non-square matrix is not defined.");
        }
        if (rows == 1)
            return data[0];
        T det = 0;
        for (int i = 0; i < columns; i++)
        {
            if (i % 2 == 0)
            {
                det += data[i] * Minor(0, i).Determinant();
            }
            else
            {
                det -= data[i] * Minor(0, i).Determinant();
            }
        }
        return det;
    }
};

#endif
