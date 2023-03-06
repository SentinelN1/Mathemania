#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

using std::vector;

template<typename T>
class Matrix {
private:
    int rows, columns;
    vector<T> data;

public:
    int Rows() const {
        return rows;
    }

    int Columns() const {
        return columns;
    }

    bool square() const {
        return rows == columns;
    }

    void clear() {
        rows = 0;
        columns = 0;
        data.clear();
    }

    // Default constructor
    Matrix() {
        rows = 0;
        columns = 0;
    }

    // Constructor
    Matrix(const int &r, const int &c, const T &t) {
        rows = r;
        columns = c;
        data = vector<T>(r * c);

        // Fills the matrix
        for (auto i: data) {
            i = t;
        }
    }

    // Destructor
    ~Matrix() = default;

    // Constructor
    // Creates matrix from initializer_list<initializer_list>
    Matrix(std::initializer_list<std::initializer_list<T>> matrix) {
        rows = matrix.size();
        columns = (matrix.begin())->size();

        for (auto row: matrix) {
            if (row.size() != columns) {
                throw std::invalid_argument("Enter rectangular matrix with a constant length of rows.");
            }
        }

        data = vector<T>(rows * columns);
        int index = 0;

        for (auto row: matrix) {
            for (auto i: row) {
                data[index] = i;
                index++;
            }
        }
    }

    // Constructor
    // Creates matrix from initializer_list
    Matrix(std::initializer_list<T> matrix) {
        rows = matrix.size();
        columns = 1;
        data = vector<T>(rows * columns);

        int index = 0;
        for (auto i: matrix) {
            data[index] = i;
            index++;
        }
    }

    // Copy constructor
    Matrix(const Matrix &other) {
        if (this != &other) {
            rows = other.rows;
            columns = other.columns;
            data = other.data;
        }
    }

    // Copy Assigment Operator0
    Matrix &operator=(const Matrix &other) {
        if (this != &other) {
            rows = other.rows;
            columns = other.columns;
            data = other.data;
        }
        return *this;
    }

    // Move Constructor
    Matrix(Matrix &&other) {
        rows = other.rows;
        columns = other.columns;
        data = other.data;
        other.clear();
    }

    // Move Assignment Operator
    Matrix &operator=(Matrix &&other) {
        if (this != &other) {
            rows = other.rows;
            columns = other.columns;
            data = other.data;
            other.clear();
        }
        return *this;
    }

    // Console output
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
        for (int i = 0; i < matrix.rows; i++) {
            if (i == 0) {
                os << std::setw(4) << "{{";
            } else {

                os << std::setw(4) << "{";
            }

            for (int j = 0; j < matrix.columns; j++) {
                os << std::setw(4) << matrix.data[i * matrix.columns + j];
                if (j < matrix.columns - 1) {
                    os << ",";
                } else {
                    os << std::setw(4) << "}";
                }
            }
            if (i < matrix.rows - 1) {
                os << std::endl;
            } else {
                os << "}";
            }
        }
        return os;
    }

    // Input from console
    friend std::istream &operator>>(std::istream &is, Matrix &matrix) {
        for (int i = 0; i < matrix.rows * matrix.columns; ++i) {
            is >> matrix.data[i];
        }
        return is;
    }

    // Matrix addition
    Matrix operator+(const Matrix &other) {
        if (rows != other.rows || columns != other.columns) {
            throw std::invalid_argument("Only matrices of equal dimensions can be added together.");
        }

        Matrix<T> matrix(rows, columns);
        for (int i = 0; i < rows * columns; i++) {
            matrix.data[i] = data[i] + other.data[i];
        }

        return matrix;
    }

    // Matrix scalar multiplication
    template<typename TScalar>
    friend Matrix operator*(const TScalar &scalar, const Matrix<T> &other) {
        Matrix<T> matrix(other);

        for (int i = 0; i < other.rows * other.columns; i++) {
            matrix.data[i] = other.data[i] * scalar;
        }

        return matrix;
    }

    // Matrix scalar multiplication
    template<typename TScalar>
    Matrix operator*(const TScalar &scalar) const {
        Matrix<T> matrix(rows, columns);

        for (int i = 0; i < rows * columns; i++) {
            matrix.data[i] = data[i] * scalar;
        }

        return matrix;
    }

    // Matrix multiplication
    Matrix operator*(const Matrix<T> &other) {
        if (columns != other.rows) {
            throw std::invalid_argument(
                    "Number of columns of the left matrix should be equal to the number of rows of the right matrix.");
        }

        Matrix<T> matrix(rows, other.columns);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < other.columns; c++) {
                T tmp = 0;
                for (int i = 0; i < columns; i++) {
                    tmp += data[columns * r + i] * other.data[other.columns * i + c];
                }
                matrix.data[other.columns * r + c] = tmp;
            }
        }

        return matrix;
    }

    // Unary operator-
    Matrix<T> operator-() const {
        return -1 * *this;
    }

    // Unary operator+
    Matrix<T> operator+() const {
        return *this;
    }

    // Matrix subtraction
    Matrix<T> operator-(const Matrix<T> &other) const {
        if (rows != other.rows || columns != other.columns) {
            throw std::invalid_argument("Matrices should be of equal dimensions.");
        }
        Matrix<T> matrix(rows, columns);
        for (int i = 0; i < rows * columns; ++i) {
            matrix.data[i] = data[i] - other.data[i];
        }
        return matrix;
    }

    // Matrix equality
    bool operator==(const Matrix<T> &other) {
        if (rows == other.rows && columns == other.columns) {
            bool tmp = true;
            for (int i = 0; i < rows * columns; i++) {
                if (data[i] != other.data[i]) {
                    tmp = false;
                    break;
                }
            }
            return tmp;
        }
        return false;
    }

    // Element of a matrix
    T &operator()(const size_t &column, const size_t &row) {
        if (row >= rows || column >= columns) {
            throw std::invalid_argument("Index out of range.");
        }
        return data[row * columns + column];
    }

    // Identity matrix
    static Matrix<T> Identity(const int &size) {
        Matrix<T> matrix(size, size);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrix.data[size * i + j] = 0;
                if (i == j) {
                    matrix.data[size * i + j] = 1;
                }
            }
        }
        return matrix;
    }

    Matrix<T> Minor(const size_t &row, const size_t &column) const {
        Matrix<T> matrix(rows - 1, columns - 1);
        for (size_t i = 0; i < rows - 1; ++i) {
            for (size_t j = 0; j < columns - 1; ++j) {
                size_t x = i;
                size_t y = j;
                if (i >= row) {
                    x = i + 1;
                }
                if (j >= column) {
                    y = j + 1;
                }
                matrix.data[i * (columns - 1) + j] = data[x * columns + y];
            }
        }
        return matrix;
    }

    T Determinant() const {
        if (rows != columns) {
            throw std::invalid_argument("Determinant of non-square matrix is not defined.");
        }
        if (rows == 1)
            return data[0];
        T det = 0;
        for (int i = 0; i < columns; i++) {
            if (i % 2 == 0) {
                det += data[i] * Minor(0, i).Determinant();
            } else {
                det -= data[i] * Minor(0, i).Determinant();
            }
        }
        return det;
    }

    Matrix<T> Transpose() const {
        Matrix<T> matrix(columns, rows);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrix(j, i) = data[i * columns + j];
            }
        }
        return matrix;
    }

    Matrix<T> Inverse() const {
        if (rows != columns) {
            throw std::invalid_argument("Non-square matrices have no Inverse.");
        }

        T det = Determinant();

        if (det == 0) {
            throw std::invalid_argument("Zero determinant.");
        }

        Matrix<T> matrix(rows, columns);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                T tmp = Minor(j, i).Determinant();
                matrix(i, j) = tmp;
                if ((i + j) % 2 != 0 && tmp != 0) {
                    matrix(i, j) = -1 * tmp;
                }
            }
        }
        matrix = (1 / det) * matrix;
        return matrix;
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