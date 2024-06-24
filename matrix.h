#ifndef MATHEMANIA_MATRIX_H_
#define MATHEMANIA_MATRIX_H_
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <iomanip>
#include <exception>
#include <vector>

typedef float Real;
// typedef double Real;
typedef long long int Integer;
typedef unsigned long long int Natural;
// typedef size_t Natural;

namespace linal
{
    class Vector2D
    {
        // protected:

    public:
        Real x, y;

        Vector2D()
        {
            x = 0.0;
            y = 0.0;
        }

        Vector2D(const Real &x_)
        {
            x = x_;
            y = x_;
        }

        Vector2D(const Real &x_, const Real &y_)
        {
            x = x_;
            y = y_;
        }

        ~Vector2D() = default;

        friend std::ostream &operator<<(std::ostream &os, const Vector2D &vector)
        {
            os << "[" << vector.x << ", " << vector.y << "]";
            return os;
        }

        static Real Dot(const Vector2D &v, const Vector2D &u)
        {
            return v.x * u.x + v.y * u.y;
        }

        static Real Norm(const Vector2D &v)
        {
            return sqrt(Dot(v, v));
        }

        static Real Rad(const Vector2D &v, const Vector2D &u)
        {
            return acos(Dot(v, u) / sqrt(Dot(v, v) * Dot(u, u)));
        }

        static Real Deg(const Vector2D &v, const Vector2D &u)
        {
            return Rad(v, u) * 180.0 / M_PI;
        }
    };

    class Vector
    {
    protected:
        std::vector<Real> values_;

    public:
        Vector()
        {
            values_ = std::vector<Real>();
        }

        Vector(const Real &x)
        {
            values_ = std::vector<Real>({x});
        }

        Vector(const Real &x, const Real &y)
        {
            values_ = std::vector<Real>({x, y});
        }

        Vector(const Real &x, const Real &y, const Real &z)
        {
            values_ = std::vector<Real>({x, y, z});
        }

        Vector(const Real &x, const Real &y, const Real &z, const Real &w)
        {
            values_ = std::vector<Real>({x, y, z, w});
        }

        Vector(const std::initializer_list<Real> &lst)
        {
            values_ = std::vector<Real>(lst);
        }

        Vector(const std::vector<Real> &vector)
        {
            values_ = vector;
        }

        Natural size() const
        {
            return values_.size();
        }

        Real operator[](const Natural &index) const
        {
            return values_[index];
        }

        Vector operator+(const Vector &vector) const
        {
            std::vector<Real> values = values_;
            for (Natural i = 0; i < values.size(); i++)
            {
                values[i] = values_[i] + vector[i];
            }
            
            return Vector(values);
        }

        Vector operator*(const Real &number) const
        {
            std::vector<Real> values = values_;
            for (Natural i = 0; i < values.size(); i++)
            {
                values[i] = number * values_[i];
            }
            
            return Vector(values);
        }
    };

    Real Dot(const Vector &vector1, const Vector &vector2)
    {
        Natural n = vector1.size();
        Natural m = vector2.size();

        if (n != m)
        {
            throw std::exception();
        }

        Real dot = 0.0;

        for (Natural i = 0; i < n; i++)
        {
            dot += vector1[i] * vector2[i];
        }

        return dot;
    }

    Real Norm(const Vector &vector)
    {
        return sqrt(Dot(vector, vector));
    }

    Real AngleRad(const Vector &vector1, const Vector &vector2)
    {
        return acos(Dot(vector1, vector2) / sqrt(Dot(vector1, vector1) * Dot(vector2, vector2)));
    }

    template <typename T>
    class Matrix
    {
    protected:
        size_t rows_, columns_;
        std::vector<T> values_;

    public:
        void clear()
        {
            values_.clear();
            rows_ = 0;
            columns_ = 0;
        }

        size_t rows() const noexcept
        {
            return rows_;
        }

        size_t columns() const noexcept
        {
            return columns_;
        }

        explicit Matrix()
        {
            rows_ = 0;
            columns_ = 0;
            values_ = std::vector<T>(rows_ * columns_);
        }

        // Constructs a square matrix
        explicit Matrix(const size_t &size)
        {
            rows_ = size;
            columns_ = size;
            values_ = std::vector<T>(rows_ * columns_);
        }

        // Constructs a (n, m) matrix
        explicit Matrix(const size_t &rows, const size_t &columns)
        {
            rows_ = rows;
            columns_ = columns;
            values_ = std::vector<T>(rows_ * columns_);
        }

        template <typename Y>
        Matrix(const std::initializer_list<Y> &list)
        {
            rows_ = list.size();
            columns_ = 1;
            values_ = std::vector<T>(rows_ * columns_);

            size_t index = 0;
            for (const auto &value : list)
            {
                values_[index] = static_cast<T>(value);
                index++;
            }
        }

        template <typename Y>
        Matrix(const std::initializer_list<std::initializer_list<Y>> &list)
        {
            rows_ = list.size();
            columns_ = list.begin()->size();
            values_ = std::vector<T>(rows_ * columns_);

            size_t row_index = 0;
            for (const auto &row : list)
            {
                if (row.size() != columns_)
                {
                    clear();
                    throw std::invalid_argument("List has an invalid shape.");
                }

                size_t column_index = 0;
                for (const auto &value : row)
                {
                    values_[row_index * columns_ + column_index] = static_cast<T>(value);
                    column_index++;
                }

                row_index++;
            }
        }

        ~Matrix() = default;

        // Copy constructor
        template <typename Y>
        explicit Matrix(const Matrix<Y> &other)
        {
            rows_ = other.rows();
            columns_ = other.columns();
            values_ = std::vector<T>(rows_ * columns_);

            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                values_[index] = static_cast<T>(other.at(index));
            }
        }

        // Move constructors
        template <typename Y>
        explicit Matrix(Matrix<Y> &&other) noexcept
        {
            rows_ = other.rows_;
            columns_ = other.columns_;
            values_ = std::vector<T>(rows_ * columns_);

            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                values_[index] = static_cast<T>(other.values_[index]);
            }
            other.clear();
        }

        T at(const size_t &index) const
        {
            if (index < 0 || rows_ * columns_ <= index)
            {
                throw std::out_of_range("Index out of range.");
            }

            return values_[index];
        }

        T at(const size_t &row, const size_t &column) const
        {
            if (row < 0 || rows_ <= row)
            {
                throw std::out_of_range("Row index out of range.");
            }

            if (column < 0 || columns_ <= column)
            {
                throw std::out_of_range("Column index out of range.");
            }

            return values_[row * columns_ + column];
        }

        // std::vector<T> &operator[](const size_t &row, const size_t &column);
        // std::vector<T> operator[](const size_t &, const size_t &) const;

        template <typename Y>
        Matrix<T> &operator=(const Matrix<Y> &other)
        {
            rows_ = other.rows();
            columns_ = other.columns();
            values_ = std::vector<T>(rows_ * columns_);

            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                values_[index] = static_cast<T>(other.at(index));
            }

            return *this;
        }

        // Move assignment operator
        template <typename Y>
        Matrix &operator=(Matrix<Y> &&other) noexcept
        {
            rows_ = other.rows_;
            columns_ = other.columns_;
            values_ = std::vector<T>(rows_ * columns_);

            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                values_[index] = static_cast<T>(other.values_[index]);
            }

            other.clear();

            return *this;
        }

        Matrix operator+() const
        {
            return *this;
        }

        // Matrix operator-() const
        // {
        //     return -1 * *this;
        // }

        // Matrix addition
        template <typename Y>
        Matrix operator+(const Matrix<Y> &other) const
        {
            if (rows_ != other.rows_ || columns_ != other.columns_)
            {
                throw std::exception();
            }

            Matrix result(rows_, columns_);
            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                result.values_[index] = values_[index] + static_cast<T>(other.values_[index]);
            }

            return result;
        }

        // Matrix-scalar multiplication
        template <typename Y>
        Matrix<T> operator*(const Y &scalar) const
        {
            Matrix result(rows_, columns_);

            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                result.values_[index] = values_[index] * static_cast<T>(scalar);
            }

            return result;
        }

        // Matrix division by scalar
        template <typename Y>
        Matrix<T> operator/(const Y &scalar) const
        {
            Matrix result(rows_, columns_);

            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                result.values_[index] = values_[index] / static_cast<T>(scalar);
            }

            return result;
        }

        // Matrix-matrix multiplication
        template <typename Y>
        Matrix<T> operator*(const Matrix<Y> &other) const
        {
            if (columns_ != other.rows_)
            {
                throw std::exception();
            }

            Matrix result;
        }

        template <typename Y>
        bool operator==(const Matrix<Y> &other) const
        {
            if (rows_ != other.rows_ || columns_ != other.columns_)
            {
                return false;
            }
            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                if (values_[index] != other.values_[index])
                {
                    return false;
                }
            }
            return true;
        }

        template <typename Y>
        bool operator!=(const Matrix<Y> &other) const
        {
            if (rows_ != other.rows_ || columns_ != other.columns_)
            {
                return true;
            }
            for (size_t index = 0; index < rows_ * columns_; index++)
            {
                if (values_[index] != other.values_[index])
                {
                    return true;
                }
            }
            return false;
        }

    private:
        // Prints the contents of the matrix to console
        friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
        {
            const int WIDTH = 4;

            for (size_t row = 0; row < matrix.rows_; row++)
            {
                if (row == 0)
                {
                    os << "{{ ";
                }
                else
                {
                    os << " { ";
                }

                // os << std::setw(WIDTH);

                for (size_t column = 0; column < matrix.columns_; column++)
                {
                    os << matrix.values_[row * matrix.columns_ + column];

                    if (column < matrix.columns_ - 1)
                    {
                        os << ", ";
                        // os << std::setw(WIDTH);
                    }
                }

                if (row < matrix.rows_ - 1)
                {
                    os << " } \n";
                }
                else
                {
                    os << " }}";
                }
            }

            return os;
        }

        // Input matrix from console
        friend std::istream &operator>>(std::istream &is, Matrix &matrix)
        {
            for (size_t row = 0; row < matrix.rows_; row++)
            {
                for (size_t column = 0; column < matrix.columns_; column++)
                {
                    is >> matrix.values_[row * matrix.columns_ + column];
                }
            }

            return is;
        }

        // Matrix Transpose() const;
        // Matrix<T> Submatrix(const size_t &, const size_t &) const;
        // T Determinant() const;
        // Matrix Minor(const size_t &row, const size_t &col) const
        // Matrix Inverse() const;
    };
}

#endif

// MATHEMANIA_MATRIX_H_

// // Identity matrix
// template <typename T>
// Matrix<T> IdentityMatrix(const size_t &size)
// {
//     Matrix<T> result(size, size);
//     for (size_t row = 0; row < size; ++row)
//     {
//         for (size_t col = 0; col < size; ++col)
//         {
//             if (row != col)
//             {
//                 result(row, col) = 0;
//             }
//             else
//             {
//                 result(row, col) = 1;
//             }
//         }
//     }
//     return result;
// }

// // Minor
// template <typename T>
// Matrix<T> Minor(const Matrix<T> &matrix, const size_t &row, const size_t &col)
// {
//     return matrix.Minor(row, col);
// }

// // Determinant
// template <typename T>
// Matrix<T> Determinant(const Matrix<T> &matrix)
// {
//     return matrix.Determinant();
// }

// // Transpose
// template <typename T>
// Matrix<T> Transpose(const Matrix<T> &matrix)
// {
//     return matrix.Transpose();
// }

// // Inverse
// template <typename T>
// Matrix<T> Inverse(const Matrix<T> &matrix)
// {
//     return matrix.Inverse();
// }
