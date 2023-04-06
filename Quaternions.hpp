#pragma once

template <typename T = double>
class Quaternions
{
private:
    T real, i_imaginary, j_imaginary, k_imaginary;

public:
    Quaternions(const T &x, const T &y, const T &z, const T &w)
    {
        real = x;
        i_imaginary = y;
        j_imaginary = z;
        k_imaginary = w;
    }

    ~Quaternions() = default;

    
};
