#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <Core/math/Mat.hpp>
#include "Math/Vector.hpp"

class Matrix
{
public:
    Matrix();
    Matrix(const Core::Mat& mat);

    static Matrix identity();
    static Matrix translate(double dx, double dy, double dz);
    static Matrix translate(const Vector& offset);
    static Matrix rotate(const Vector& axis, double angle);
    static Matrix scale(double fx, double fy, double fz);
    static Matrix scale(const Vector& factors);
    static Matrix perspective(double fov, double near, double far);

    static Matrix fpsModel(const Vector& eye, double pitch, double yaw);

    double det() const;
    Matrix operator*(const Matrix& right) const;
    Matrix operator*(double val) const;
    Vector operator*(const Vector& vec) const;
    operator Core::Mat() const;

    Matrix transpose() const;
    Matrix inverse() const;

protected:
    explicit Matrix(const double mat[16]);

private:
    double data[16];
};

Matrix operator*(double val, const Matrix& mat);
Vector operator*(const Vector& vec, const Matrix& mat);

#endif //MATRIX_HPP
