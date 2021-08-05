#include "Math/Matrix.hpp"


Matrix::Matrix()
{
    for (double& elem : data)
        elem = 0.0;
}

Matrix::Matrix(const Core::Mat &mat)
{
    for (int i = 0; i < 16; i++)
        data[i] = mat.data[i];
}

Matrix::Matrix(const double *mat)
{
    for (int i = 0; i < 16; i++)
        data[i] = mat[i];
}

Matrix Matrix::identity()
{
    Matrix res = Matrix();

    for (int i = 0; i < 16; i += 5)
        res.data[i] = 1;

    return res;
}

Matrix Matrix::translate(double dx, double dy, double dz)
{
    Matrix res = identity();

    res.data[3] = dx;
    res.data[7] = dy;
    res.data[11] = dz;

    return res;
}

Matrix Matrix::translate(const Vector &offset)
{
    return translate(offset.getX(), offset.getY(), offset.getZ());
}

Matrix Matrix::rotate(const Vector &axis, double angle)
{
    Matrix res = identity();
    double x = axis.getX(), y = axis.getY(), z = axis.getZ();
    double c = std::cos(angle), s = std::sin(angle);
    double imc = 1 - c;

    res.data[0] = c + x * x * imc;
    res.data[1] = x * y * imc - z * s;
    res.data[2] = x * z * imc + y * s;
    res.data[4] = x * y * imc + z * s;
    res.data[5] = c + y * y * imc;
    res.data[6] = y * z * imc - x * s;
    res.data[8] = x * z * imc - y * s;
    res.data[9] = y * z * imc + x * s;
    res.data[10] = c + z * z * imc;

    return res;
}

Matrix Matrix::scale(double fx, double fy, double fz)
{
    Matrix res = identity();

    res.data[0] = fx;
    res.data[1] = fy;
    res.data[2] = fz;

    return res;
}

Matrix Matrix::scale(const Vector &factors)
{
    return scale(factors.getX(), factors.getY(), factors.getZ());
}

Matrix Matrix::perspective(double fov, double near, double far)
{
    Matrix res;
    double s = 1 / std::tan(fov / 2);

    res.data[0] = s;
    res.data[5] = s;
    res.data[10] = far / (far - near);
    res.data[11] = near * far / (near - far);
    res.data[14] = 1;

    return res;
}

double Matrix::det() const
{
    double res = 0;

    res += data[0] * data[5] * data[10] * data[15];
    res += data[1] * data[6] * data[11] * data[12];
    res += data[2] * data[7] * data[ 8] * data[13];
    res += data[3] * data[4] * data[ 9] * data[14];

    res -= data[0] * data[7] * data[10] * data[13];
    res -= data[1] * data[4] * data[11] * data[14];
    res -= data[2] * data[5] * data[ 8] * data[15];
    res -= data[3] * data[6] * data[ 9] * data[12];

    return res;
}

Matrix Matrix::operator*(const Matrix &right) const
{
    Matrix res;

    for (int i = 0; i < 16; i += 4)
        for (int j = 0; j < 4; j++)
            for (int k = 0, k4 = 0; k < 4; k++, k4 += 4)
                res.data[i + j] += data[i + k] * right.data[k4 + j];

    return res;
}

Matrix Matrix::operator*(double val) const
{
    Matrix res;

    for (int i = 0; i < 16; i++)
        res.data[i] = val * data[i];

    return res;
}

Vector Matrix::operator*(const Vector &vec) const
{
    return Vector(
            vec.getX() * data[ 0] + vec.getY() * data[ 1] + vec.getZ() * data[ 2] + vec.getW() * data[ 3],
            vec.getX() * data[ 4] + vec.getY() * data[ 5] + vec.getZ() * data[ 6] + vec.getW() * data[ 7],
            vec.getX() * data[ 8] + vec.getY() * data[ 9] + vec.getZ() * data[10] + vec.getW() * data[11],
            vec.getX() * data[12] + vec.getY() * data[ 13] + vec.getZ() * data[14] + vec.getW() * data[15]
    );
}

Matrix Matrix::inverse() const
{
    Matrix inv;

    inv.data[0] = data[5] * data[10] * data[15] -
                  data[5] * data[11] * data[14] -
                  data[9] * data[6] * data[15] +
                  data[9] * data[7] * data[14] +
                  data[13] * data[6] * data[11] -
                  data[13] * data[7] * data[10];

    inv.data[4] = -data[4] * data[10] * data[15] +
                  data[4] * data[11] * data[14] +
                  data[8] * data[6] * data[15] -
                  data[8] * data[7] * data[14] -
                  data[12] * data[6] * data[11] +
                  data[12] * data[7] * data[10];

    inv.data[8] = data[4] * data[9] * data[15] -
                  data[4] * data[11] * data[13] -
                  data[8] * data[5] * data[15] +
                  data[8] * data[7] * data[13] +
                  data[12] * data[5] * data[11] -
                  data[12] * data[7] * data[9];

    inv.data[12] = -data[4] * data[9] * data[14] +
                   data[4] * data[10] * data[13] +
                   data[8] * data[5] * data[14] -
                   data[8] * data[6] * data[13] -
                   data[12] * data[5] * data[10] +
                   data[12] * data[6] * data[9];

    inv.data[1] = -data[1] * data[10] * data[15] +
                  data[1] * data[11] * data[14] +
                  data[9] * data[2] * data[15] -
                  data[9] * data[3] * data[14] -
                  data[13] * data[2] * data[11] +
                  data[13] * data[3] * data[10];

    inv.data[5] = data[0] * data[10] * data[15] -
                  data[0] * data[11] * data[14] -
                  data[8] * data[2] * data[15] +
                  data[8] * data[3] * data[14] +
                  data[12] * data[2] * data[11] -
                  data[12] * data[3] * data[10];

    inv.data[9] = -data[0] * data[9] * data[15] +
                  data[0] * data[11] * data[13] +
                  data[8] * data[1] * data[15] -
                  data[8] * data[3] * data[13] -
                  data[12] * data[1] * data[11] +
                  data[12] * data[3] * data[9];

    inv.data[13] = data[0] * data[9] * data[14] -
                   data[0] * data[10] * data[13] -
                   data[8] * data[1] * data[14] +
                   data[8] * data[2] * data[13] +
                   data[12] * data[1] * data[10] -
                   data[12] * data[2] * data[9];

    inv.data[2] = data[1] * data[6] * data[15] -
                  data[1] * data[7] * data[14] -
                  data[5] * data[2] * data[15] +
                  data[5] * data[3] * data[14] +
                  data[13] * data[2] * data[7] -
                  data[13] * data[3] * data[6];

    inv.data[6] = -data[0] * data[6] * data[15] +
                  data[0] * data[7] * data[14] +
                  data[4] * data[2] * data[15] -
                  data[4] * data[3] * data[14] -
                  data[12] * data[2] * data[7] +
                  data[12] * data[3] * data[6];

    inv.data[10] = data[0] * data[5] * data[15] -
                   data[0] * data[7] * data[13] -
                   data[4] * data[1] * data[15] +
                   data[4] * data[3] * data[13] +
                   data[12] * data[1] * data[7] -
                   data[12] * data[3] * data[5];

    inv.data[14] = -data[0] * data[5] * data[14] +
                   data[0] * data[6] * data[13] +
                   data[4] * data[1] * data[14] -
                   data[4] * data[2] * data[13] -
                   data[12] * data[1] * data[6] +
                   data[12] * data[2] * data[5];

    inv.data[3] = -data[1] * data[6] * data[11] +
                  data[1] * data[7] * data[10] +
                  data[5] * data[2] * data[11] -
                  data[5] * data[3] * data[10] -
                  data[9] * data[2] * data[7] +
                  data[9] * data[3] * data[6];

    inv.data[7] = data[0] * data[6] * data[11] -
                  data[0] * data[7] * data[10] -
                  data[4] * data[2] * data[11] +
                  data[4] * data[3] * data[10] +
                  data[8] * data[2] * data[7] -
                  data[8] * data[3] * data[6];

    inv.data[11] = -data[0] * data[5] * data[11] +
                   data[0] * data[7] * data[9] +
                   data[4] * data[1] * data[11] -
                   data[4] * data[3] * data[9] -
                   data[8] * data[1] * data[7] +
                   data[8] * data[3] * data[5];

    inv.data[15] = data[0] * data[5] * data[10] -
                   data[0] * data[6] * data[9] -
                   data[4] * data[1] * data[10] +
                   data[4] * data[2] * data[9] +
                   data[8] * data[1] * data[6] -
                   data[8] * data[2] * data[5];

    double det = 1 / (data[0] * inv.data[0]
                      + data[1] * inv.data[4]
                      + data[2] * inv.data[8]
                      + data[3] * inv.data[12]);

    for (double & i : inv.data)
        i *= det;

    return inv;
}

Matrix::operator Core::Mat() const
{
    Core::Mat res;

    for (int i = 0; i < 16; i++)
        res.data[i] = data[i];

    return res;
}

Matrix operator*(double val, const Matrix &mat)
{
    return mat * val;
}

Vector operator*(const Vector &vec, const Matrix &mat)
{
    return mat * vec;
}
