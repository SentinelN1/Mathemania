#ifndef MATHEMANIA_QUATERNION_H_
#define MATHEMANIA_QUATERNION_H_

#include <cmath>
#include <iostream>

typedef long double Real;

class Quaternion
{
protected:
    Real a_, b_, c_, d_;

public:
    Quaternion(const Real &a = 0, const Real &b = 0, const Real &c = 0, const Real &d = 0)
    {
        a_ = a;
        b_ = b;
        c_ = c;
        d_ = d;
    }

    Quaternion conj() const
    {
        return Quaternion(a_, -b_, -c_, -d_);
    }

    Real abs2() const
    {
        return a_ * a_ + b_ * b_ + c_ * c_ + d_ * d_;
    }

    Real abs() const
    {
        return sqrtl(a_ * a_ + b_ * b_ + c_ * c_ + d_ * d_);
    }

    friend std::ostream &operator<<(std::ostream &os, const Quaternion &q)
    {
        // TODO: fancy output
        os << "(" << q.a_ << ")+(" << q.b_ << ")i+(" << q.c_ << ")j+(" << q.d_ << ")k";
        return os;
    }

    Quaternion operator+(const Quaternion &other) const
    {
        return Quaternion(a_ + other.a_, b_ + other.a_, c_ + other.c_, d_ + other.d_);
    }

    Quaternion operator*(const Quaternion &other) const
    {
        return Quaternion(a_ + other.a_, b_ + other.a_, c_ + other.c_, d_ + other.d_);
    }
};

#endif