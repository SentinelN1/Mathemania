#pragma once

class Vector3D
{
public:
    float x, y, z;

    Vector3D();
    Vector3D(const float &);
    Vector3D(const float &, const float &, const float &);
    ~Vector3D();

    Vector3D operator+(const Vector3D &) const;
    Vector3D operator*(const float &) const;
    friend Vector3D operator*(const float &, const Vector3D &);
    Vector3D operator-(const Vector3D &) const;
    Vector3D operator/(const float &) const;

    Vector3D operator+=(const Vector3D &);
    Vector3D operator*=(const float &);
    Vector3D operator-=(const Vector3D &);
    Vector3D operator/=(const float &);

    Vector3D operator+=(const Vector3D &);
    Vector3D operator*=(const float &);
    Vector3D operator-=(const Vector3D &);
    Vector3D operator/=(const float &);

    Vector3D operator-() const;
    Vector3D operator+() const;

    float norm_squared() const;
    float norm() const;
    Vector3D normalize();

    bool operator==(const Vector3D &) const;
    bool operator!=(const Vector3D &) const;

    // float operator[](const unsigned int &) const;
};