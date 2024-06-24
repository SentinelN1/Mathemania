#define _USE_MATH_DEFINES

#include "vector3.h"
#include <cmath>

Vector3D::Vector3D()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

Vector3D::Vector3D(const float &value)
{
    this->x = value;
    this->y = value;
    this->z = value;
}

Vector3D::Vector3D(const float &x, const float &y, const float &z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3D::~Vector3D() = default;

Vector3D Vector3D::operator+(const Vector3D &other) const
{
    return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3D Vector3D::operator*(const float &multiplier) const
{
    return Vector3D(this->x * multiplier, this->y * multiplier, this->z * multiplier);
}

Vector3D operator*(const float &multiplier, const Vector3D &vector)
{
    return Vector3D(vector.x * multiplier, vector.y * multiplier, vector.z * multiplier);
}

Vector3D Vector3D::operator-(const Vector3D &other) const
{
    return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3D Vector3D::operator/(const float &divisor) const
{
    return Vector3D(this->x / divisor, this->y / divisor, this->z / divisor);
}

Vector3D Vector3D::operator+=(const Vector3D &other)
{
    this->x = this->x + other.x;
    this->y = this->y + other.y;
    this->z = this->z + other.z;
    return *this;
}

Vector3D Vector3D::operator*=(const float &multiplier)
{
    this->x = this->x * multiplier;
    this->y = this->y * multiplier;
    this->z = this->z * multiplier;
    return *this;
}

Vector3D Vector3D::operator-=(const Vector3D &other)
{
    this->x = this->x - other.x;
    this->y = this->y - other.y;
    this->z = this->z - other.z;
    return *this;
}

Vector3D Vector3D::operator/=(const float &divisor)
{
    this->x = this->x / divisor;
    this->y = this->y / divisor;
    this->z = this->z / divisor;
    return *this;
}

Vector3D Vector3D::operator+() const
{
    return Vector3D(x, y, z);
}

Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

bool Vector3D::operator==(const Vector3D &other) const
{
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

bool Vector3D::operator!=(const Vector3D &other) const
{
    return this->x != other.x || this->y != other.y || this->z != other.z;
}

float Vector3D::norm_squared() const
{
    return this->x * this->x + this->y * this->y + this->z * this->z;
}

float Vector3D::norm() const
{
    return sqrt(this->norm_squared());
}

Vector3D Vector3D::normalize()
{
    float norm = this->norm();
    this->x /= norm;
    this->y /= norm;
    this->z /= norm;
    return *this;
}

float Dot(const Vector3D &u, const Vector3D &v)
{
    return u.x * v.x + u.y * v.y + u.z * v.z;
}

float NormSquared(const Vector3D &u)
{
    // return u.x * u.x + u.y * u.y + u.z * u.z
    return Dot(u, u);
}

float Norm(const Vector3D &u)
{
    // return sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    // return sqrt(NormSquared(u));
    return sqrt(Dot(u, u));
}

Vector3D Cross(const Vector3D &u, const Vector3D &v)
{
    float x = u.y * v.z - u.z * v.y;
    float y = -u.x * v.z + u.z * v.x;
    float z = u.x * v.y - u.y * v.x;
    return Vector3D(x, y, z);
}

float Cos(const Vector3D &u, const Vector3D &v)
{
    return Dot(u, v) / sqrt(Dot(u, u) * Dot(v, v));
}

float AngleRad(const Vector3D &u, const Vector3D &v)
{
    return acos(Cos(u, v));
    // return acos(Dot(u, v) / sqrt(Dot(u, u) * Dot(v, v)));
}

float AngleDeg(const Vector3D &u, const Vector3D &v)
{
    return AngleRad(u, v) * 180.0 / M_PI;
    // return acos(Dot(u, v) / sqrt(Dot(u, u) * Dot(v, v))) * 180.0 / M_PI;
}

Vector3D TriangleNormal(const Vector3D &A, const Vector3D &B, const Vector3D &C)
{
    // Vector3D r1 = B - A;
    // Vector3D r2 = C - A;
    // Vector3D n = Cross(r1, r2);
    // n.normalize();
    // return n;

    return Cross(B - A, C - A).normalize();
}

int main()
{
    Vector3D vec1(0.6, 0.8, 1.0);
    Vector3D vec2(0.8, 1.0, 0.6);

    Vector3D sum = vec1 + vec2;
    Vector3D dif = vec1 - vec2;
    Vector3D mul = vec1 * (-1);
    Vector3D mul2 = -2 * vec2;
    Vector3D div = vec1 / 3;

    float norm2 = NormSquared(vec1);
    float norm = Norm(vec1);

    float dot = Dot(vec1, vec2);
    Vector3D cross = Cross(vec1, vec2);
    float cos = Cos(vec1, vec2);
    float deg = AngleRad(vec1, vec2);
    float rad = AngleDeg(vec1, vec2);

    Vector3D A(1, 0, 0);
    Vector3D B(0, 1, 0);
    Vector3D C(0, 0, 1);

    Vector3D n = TriangleNormal(A, B, C);

    return 0;
}
