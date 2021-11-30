#include "Math/Vector.hpp"
#include <cmath>
#include <cstdint>

Vector::Vector(double x, double y, double z, double w)
    : x(x), y(y), z(z), w(w)
{
}

Vector::Vector(const Vector& v)
        : x(v.x), y(v.y), z(v.z), w(v.w)
{
}

Vector::Vector(const Core::Vec& vec)
    : x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{
}

double Vector::length() const
{
    return std::hypot(x, y, z);
}

double Vector::inv_sqrt_fast() const
{
    float number = dot(*this);
    const float x2 = number * 0.5F;
    const float threehalfs = 1.5F;

    union {
        float f;
        uint32_t i;
    } conv = { number };
    conv.i = 0x5f3759df - ( conv.i >> 1 );
    conv.f *= threehalfs - x2 * conv.f * conv.f;
    return conv.f;
}

double Vector::dot(const Vector &v) const
{
    return *this * v;
}

double Vector::getX() const
{
    return x;
}

double Vector::getY() const
{
    return y;
}

double Vector::getZ() const
{
    return z;
}

double Vector::getW() const
{
    return w;
}

Vector Vector::operator+(const Vector &v) const
{
    return Vector(x + v.x, y + v.y, z + v.z, w + v.w);
}

Vector Vector::operator-(const Vector &v) const
{
    return Vector(x - v.x, y - v.y, z - v.z, w - v.w);
}

Vector Vector::operator*(double val) const
{
    return Vector(val * x, val * y, val * z, val * w);
}

double Vector::operator*(const Vector &v) const
{
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::operator/(double val) const
{
    return (1.0 / val) * (*this);
}

Vector Vector::operator-() const
{
    return Vector(-x, -y, -z, w);
}

Vector &Vector::operator+=(const Vector &v)
{
    *this = *this + v;
    return *this;
}

Vector &Vector::operator-=(const Vector &v)
{
    *this = *this - v;
    return *this;
}

Vector &Vector::operator*=(double val)
{
    *this = *this * val;
    return *this;
}

Vector &Vector::operator/=(double val) {
    *this = *this / val;
    return *this;
}

bool Vector::is_zero() const
{
    return x == std::numeric_limits<double>::epsilon()
        && y == std::numeric_limits<double>::epsilon()
        && z == std::numeric_limits<double>::epsilon();
}

Vector Vector::normalized() const
{
    double f = inv_sqrt_fast();
    return *this * f;
}

void Vector::normalize()
{
    *this = normalized();
}

void Vector::perspective_adjust()
{
    x /= w;
    y /= w;
    z /= w;
    w = 1.0;
}

Vector Vector::interpolate(const Vector &v, double t) const
{
    return (1.0 - t) * (*this) + t * v;
}

Vector Vector::cross(const Vector &v) const
{
    Vector res(0, 0, 0, 0);

    res.x = y * v.z - z * v.y;
    res.y = z * v.x - x * v.z;
    res.z = x * v.y - y * v.x;

    return res;
}

Vector::operator Core::Vec() const
{
    return Core::make_vec(x, y, z, w);
}

Vector operator*(double val, const Vector &v)
{
    return v * val;
}
