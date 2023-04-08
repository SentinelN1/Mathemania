#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

namespace matrix
{
    template <typename T = double>
    class Matrix
    {
    private:
        size_t rows, columns;
        std::vector<T> data;

    public:
        // Number of rows
        size_t Rows() const
        {
            return rows;
        }

        // Number of columns
        size_t Columns() const
        {
            return columns;
        }

        // Addressing matrix elements
        // T &operator[](const size_t &index)
        // {
        //     if (index >= rows * columns)
        //     {
        //         throw std::invalid_argument("Index out of range.");
        //     }
        //     return data[index];
        // }

        // T operator[](const size_t &index) const
        // {
        //     if (index >= rows * columns)
        //     {
        //         throw std::invalid_argument("Index out of range.");
        //     }
        //     return data[index];
        // }

        T &operator()(const size_t &row, const size_t &col)
        {
            if (row >= rows || col >= columns)
            {
                throw std::invalid_argument("Index out of range.");
            }
            return data[row * columns + col];
        }

        T operator()(const size_t &row, const size_t &col) const
        {
            if (row >= rows || col >= columns)
            {
                throw std::invalid_argument("Index out of range.");
            }
            return data[row * columns + col];
        }

        // Cheaks wheter the matrix is square
        bool IsSquare() const
        {
            return rows == columns;
        }

        // Clears the contents of the matrix
        void Clear()
        {
            rows = 0;
            columns = 0;
            data.clear();
        }

        // Default constructor
        Matrix()
        {
            rows = 0;
            columns = 0;
        }

        // Constructor
        Matrix(const size_t &row, const size_t &col, const T &elem = 0)
        {
            rows = row;
            columns = col;
            data = std::vector<T>(row * col);

            // Fills the matrix
            for (auto &i : data)
            {
                i = elem;
            }
        }

        // Destructor
        ~Matrix() = default;

        // Constructor from initializer_list<initializer_list>
        Matrix(const std::initializer_list<std::initializer_list<T>> &matrix)
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

            data = std::vector<T>(rows * columns);
            size_t index = 0;
            for (auto row : matrix)
            {
                for (auto i : row)
                {
                    data[index] = i;
                    index++;
                }
            }
        }

        // Constructor from initializer_list
        Matrix(const std::initializer_list<T> &matrix)
        {
            rows = matrix.size();
            columns = 1;
            data = std::vector<T>(rows * columns);

            size_t index = 0;
            for (auto i : matrix)
            {
                data[index] = i;
                index++;
            }
        }

        // Copy Constructor
        Matrix(const Matrix &other)
        {
            if (this != &other)
            {
                rows = other.rows;
                columns = other.columns;
                data = other.data;
            }
        }

        // Copy Assigment Operator
        Matrix &operator=(const Matrix &other)
        {
            if (this != &other)
            {
                rows = other.rows;
                columns = other.columns;
                data = other.data;
            }
            return *this;
        }

        // Move Constructor
        Matrix(Matrix &&matrix) noexcept
        {
            rows = matrix.rows;
            columns = matrix.columns;
            data = matrix.data;
            matrix.Clear();
        }

        // Move Assignment Operator
        Matrix &operator=(Matrix &&other) noexcept
        {
            if (this != &other)
            {
                rows = other.rows;
                columns = other.columns;
                data = other.data;
                other.Clear();
            }
            return *this;
        }

        // Console output
        friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
        {
            for (size_t row = 0; row < matrix.rows; ++row)
            {
                if (row == 0)
                {
                    os << std::setw(4) << "{{";
                }
                else
                {

                    os << std::setw(4) << "{";
                }
                for (size_t col = 0; col < matrix.columns; ++col)
                {
                    os << std::setw(4) << matrix.data[row * matrix.columns + col];
                    if (col < matrix.columns - 1)
                    {
                        os << ",";
                    }
                    else
                    {
                        os << std::setw(4) << "}";
                    }
                }
                if (row < matrix.rows - 1)
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
        friend std::istream &operator>>(std::istream &is, Matrix &matrix)
        {
            for (size_t i = 0; i < matrix.rows * matrix.columns; ++i)
            {
                is >> matrix[i];
            }
            return is;
        }

        // Matrix addition
        Matrix operator+(const Matrix &other) const
        {
            if (rows != other.rows || columns != other.columns)
            {
                throw std::invalid_argument("Only matrices of equal dimensions can be added together.");
            }
            Matrix result = *this;
            for (size_t i = 0; i < rows * columns; ++i)
            {
                result[i] = data[i] + other[i];
            }
            return result;
        }

        // Scalar-matrix multiplication
        template <typename TScalar>
        friend Matrix operator*(const TScalar &scalar, const Matrix &matrix)
        {
            Matrix result = matrix;
            for (size_t i = 0; i < matrix.rows * matrix.columns; ++i)
            {
                result[i] = matrix[i] * scalar;
            }
            return result;
        }

        // Matrix-scalar multiplication
        template <typename TScalar>
        Matrix operator*(const TScalar &scalar) const
        {
            Matrix result = *this;
            for (size_t i = 0; i < rows * columns; ++i)
            {
                result[i] = data[i] * scalar;
            }
            return result;
        }

        // Matrix division by scalar
        template <typename TScalar>
        Matrix operator/(const TScalar &scalar) const
        {
            Matrix result = *this;
            for (size_t i = 0; i < rows * columns; ++i)
            {
                result[i] = data[i] / scalar;
            }
            return result;
        }

        // Matrix-matrix multiplication
        Matrix operator*(const Matrix &other) const
        {
            if (columns != other.rows)
            {
                throw std::invalid_argument(
                    "Number of columns of the first result should be equal to the number of rows of the second result.");
            }
            Matrix result(rows, other.columns);
            for (size_t row = 0; row < rows; ++row)
            {
                for (size_t col = 0; col < other.columns; ++col)
                {
                    T tmp = 0;
                    for (size_t i = 0; i < columns; ++i)
                    {
                        tmp += data(row, i) * other(i, col);
                    }
                    result(row, col) = tmp;
                }
            }
            return result;
        }

        // Unary operator+
        Matrix operator+() const
        {
            return *this;
        }

        // Unary operator-
        Matrix operator-() const
        {
            return (-1) * *this;
        }

        // Matrix subtraction
        Matrix operator-(const Matrix &other) const
        {
            if (rows != other.rows || columns != other.columns)
            {
                throw std::invalid_argument("Matrices should be of equal dimensions.");
            }
            Matrix result(rows, columns);
            for (size_t i = 0; i < rows * columns; ++i)
            {
                result[i] = data[i] - other[i];
            }
            return result;
        }

        // Matrix equality operator
        bool operator==(const Matrix &other) const
        {
            if (rows != other.rows || columns != other.columns)
            {
                return false;
            }
            for (size_t i = 0; i < rows * columns; ++i)
            {
                if (data[i] != other[i])
                {
                    return false;
                }
            }
            return true;
        }

        // Matrix inequality operator
        bool operator!=(const Matrix &other) const
        {
            if (rows != other.rows || columns != other.columns)
            {
                return true;
            }
            for (size_t i = 0; i < rows * columns; ++i)
            {
                if (data[i] != other[i])
                {
                    return true;
                }
            }
            return false;
        }

        Matrix Minor(const size_t &row, const size_t &col) const
        {
            Matrix result(rows - 1, columns - 1);
            for (size_t i = 0; i < rows - 1; ++i)
            {
                for (size_t j = 0; j < columns - 1; ++j)
                {
                    size_t x = i;
                    size_t y = j;
                    if (i >= row)
                    {
                        x = i + 1;
                    }
                    if (j >= col)
                    {
                        y = j + 1;
                    }
                    result(i, j) = data[x * columns + y];
                }
            }
            return result;
        }

        T Determinant() const
        {
            if (!IsSquare())
            {
                throw std::invalid_argument("Determinant of non-square matrix is not defined.");
            }
            if (rows == 1)
                return data[0];
            T det = 0;
            for (size_t col = 0; col < columns; ++col)
            {
                if (col % 2 == 0)
                {
                    det += data[col] * Minor(0, col).Determinant();
                }
                else
                {
                    det -= data[col] * Minor(0, col).Determinant();
                }
            }
            return det;
        }

        Matrix Transpose() const
        {
            Matrix result(columns, rows);
            for (size_t row = 0; row < rows; ++row)
            {
                for (size_t col = 0; col < columns; ++col)
                {
                    result(row, col) = data[row * columns + col];
                }
            }
            return result;
        }

        Matrix Inverse() const
        {
            if (!IsSquare())
            {
                throw std::invalid_argument("Non-square matrices have no inverse.");
            }

            T det = Determinant();
            if (det == 0)
            {
                throw std::invalid_argument("Zero determinant matrices have no inverse.");
            }

            Matrix result(rows, columns);
            for (size_t row = 0; row < rows; ++row)
            {
                for (size_t col = 0; col < columns; ++col)
                {
                    T tmp = Minor(col, row).Determinant();
                    result(row, col) = tmp;
                    if ((row + col) % 2 != 0 && tmp != 0)
                    {
                        result(row, col) = -1 * tmp;
                    }
                }
            }
            result = result / det;
            return result;
        }

        // Matrix<T> Power(const int &power) const
        // {
        // if (rows != columns)
        // {
        //     throw std::invalid_argument("");
        // }
        // if (power == 0)
        // {
        //     return Identity(rows);
        // }
        // if (power == 0)
        // }

        // int Rank() const
        // {
        // }
    };

    // Identity matrix
    template <typename T>
    Matrix<T> IdentityMatrix(const size_t &size)
    {
        Matrix<T> result(size, size);
        for (size_t row = 0; row < size; ++row)
        {
            for (size_t col = 0; col < size; ++col)
            {
                if (row != col)
                {
                    result(row, col) = 0;
                }
                else
                {
                    result(row, col) = 1;
                }
            }
        }
        return result;
    }

    // Minor
    template <typename T>
    Matrix<T> Minor(const Matrix<T> &matrix, const size_t &row, const size_t &col)
    {
        return matrix.Minor(row, col);
    }

    // Determinant
    template <typename T>
    Matrix<T> Determinant(const Matrix<T> &matrix)
    {
        return matrix.Determinant();
    }

    // Transpose
    template <typename T>
    Matrix<T> Transpose(const Matrix<T> &matrix)
    {
        return matrix.Transpose();
    }

    // Inverse
    template <typename T>
    Matrix<T> Inverse(const Matrix<T> &matrix)
    {
        return matrix.Inverse();
    }
}
