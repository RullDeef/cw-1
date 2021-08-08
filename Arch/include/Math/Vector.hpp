#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <Core/math/Vec.hpp>


class Vector
{
public:
    explicit Vector(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0);
    Vector(const Vector& v);
    Vector(const Core::Vec& vec);
    double length() const;
    double getX() const;
    double getY() const;
    double getZ() const;
    double getW() const;
    double inv_sqrt_fast() const;
    bool is_zero() const;
    Vector normalized() const;
    void normalize();
    void perspective_adjust();
    Vector interpolate(const Vector& v, double t) const;
    double dot(const Vector& v) const;
    Vector cross(const Vector& v) const;

    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);
    Vector& operator*=(double val);
    Vector& operator/=(double val);
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(double val) const;
    double operator*(const Vector& v) const;
    Vector operator/(double val) const;
    Vector operator-() const;
    operator Core::Vec() const;

private:
    double x;
    double y;
    double z;
    double w;
};

Vector operator*(double val, const Vector& v);

#endif //VECTOR_HPP
