#include "Mat.hpp"
#include <cmath>


namespace Core
{

inline Mat make_mat_zero()
{
    return Mat {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
     };
}

inline Mat make_mat_id()
{
    return Mat {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
}

inline Mat make_mat_translation(double dx, double dy, double dz)
{
    return Mat {
        1, 0, 0, dx,
        0, 1, 0, dy,
        0, 0, 1, dz,
        0, 0, 0, 1
    };
}

inline Mat make_mat_translation(const Vec& offset)
{
    return Mat {
        1, 0, 0, offset.x,
        0, 1, 0, offset.y,
        0, 0, 1, offset.z,
        0, 0, 0, 1
    };
}

inline Mat make_mat_rotation(const Vec& axis, double angle)
{
    double x = axis.x, y = axis.y, z = axis.z;
    double c = std::cos(angle), s = std::sin(angle);
    double imc = 1 - c;

    return Mat {
        c + x * x * imc,        x * y * imc - z * s,    x * z * imc + y * s,    0,
        x * y * imc + z * s,    c + y * y * imc,        y * z * imc - x * s,    0,
        x * z * imc - y * s,    y * z * imc + x * s,    c + z * z * imc,        0,
        0, 0, 0, 1
    };
}

inline Mat make_mat_scale(double fx, double fy, double fz)
{
    return Mat {
        fx, 0, 0, 0,
        0, fy, 0, 0,
        0, 0, fz, 0,
        0, 0, 0, 1
    };
}

inline Mat make_mat_scale(const Vec& factors)
{
    return Mat {
        factors.x, 0, 0, 0,
        0, factors.y, 0, 0,
        0, 0, factors.z, 0,
        0, 0, 0, 1
    };
}

inline Mat make_mat_perspective(double fov, double near, double far)
{
    double s = 1 / std::tan(fov / 2);

    return Mat {
        s, 0, 0, 0,
        0, s, 0, 0,
        0, 0, far / (near - far), -1,
        0, 0, near * far / (near - far), 0
    };
}

inline double det(const Mat& mat)
{
    double res = 0;

    res += mat.data[0] * mat.data[5] * mat.data[10] * mat.data[15];
    res += mat.data[1] * mat.data[6] * mat.data[11] * mat.data[12];
    res += mat.data[2] * mat.data[7] * mat.data[ 8] * mat.data[13];
    res += mat.data[3] * mat.data[4] * mat.data[ 9] * mat.data[14];

    res -= mat.data[0] * mat.data[7] * mat.data[10] * mat.data[13];
    res -= mat.data[1] * mat.data[4] * mat.data[11] * mat.data[14];
    res -= mat.data[2] * mat.data[5] * mat.data[ 8] * mat.data[15];
    res -= mat.data[3] * mat.data[6] * mat.data[ 9] * mat.data[12];

    return res;
}

inline Mat operator*(const Mat& left, const Mat& right)
{
    Mat res = make_mat_zero();

    for (int i = 0; i < 16; i += 4)
        for (int j = 0; j < 4; j++)
            for (int k = 0, k4 = 0; k < 4; k++, k4 += 4)
                res.data[i + j] += left.data[i + k] * right.data[k4 + j];

    return res;
}

inline Mat operator*(const Mat& mat, double val)
{
    Mat res;

    for (int i = 0; i < 16; i++)
        res.data[i] = val * mat.data[i];

    return res;
}

inline Mat operator*(double val, const Mat& mat)
{
    Mat res;

    for (int i = 0; i < 16; i++)
        res.data[i] = val * mat.data[i];

    return res;
}

inline Vec operator*(const Vec& vec, const Mat& mat)
{
    return make_pos(
        vec.x * mat.data[0] + vec.y * mat.data[4] + vec.z * mat.data[ 8] + vec.w * mat.data[12],
        vec.x * mat.data[1] + vec.y * mat.data[5] + vec.z * mat.data[ 9] + vec.w * mat.data[13],
        vec.x * mat.data[2] + vec.y * mat.data[6] + vec.z * mat.data[10] + vec.w * mat.data[14],
        vec.x * mat.data[3] + vec.y * mat.data[7] + vec.z * mat.data[11] + vec.w * mat.data[15]
    );
}

inline Vec operator*(const Mat& mat, const Vec& vec)
{
    return make_pos(
        vec.x * mat.data[ 0] + vec.y * mat.data[ 1] + vec.z * mat.data[ 2] + vec.w * mat.data[ 3],
        vec.x * mat.data[ 4] + vec.y * mat.data[ 5] + vec.z * mat.data[ 6] + vec.w * mat.data[ 7],
        vec.x * mat.data[ 8] + vec.y * mat.data[ 9] + vec.z * mat.data[10] + vec.w * mat.data[11],
        vec.x * mat.data[12] + vec.y * mat.data[13] + vec.z * mat.data[14] + vec.w * mat.data[15]
    );
}

inline Mat transpose(const Mat& mat);

inline Mat inverse(const Mat& mat)
{
    Mat inv;

    inv.data[0] = mat.data[5] * mat.data[10] * mat.data[15] -
        mat.data[5] * mat.data[11] * mat.data[14] -
        mat.data[9] * mat.data[6] * mat.data[15] +
        mat.data[9] * mat.data[7] * mat.data[14] +
        mat.data[13] * mat.data[6] * mat.data[11] -
        mat.data[13] * mat.data[7] * mat.data[10];

    inv.data[4] = -mat.data[4] * mat.data[10] * mat.data[15] +
        mat.data[4] * mat.data[11] * mat.data[14] +
        mat.data[8] * mat.data[6] * mat.data[15] -
        mat.data[8] * mat.data[7] * mat.data[14] -
        mat.data[12] * mat.data[6] * mat.data[11] +
        mat.data[12] * mat.data[7] * mat.data[10];

    inv.data[8] = mat.data[4] * mat.data[9] * mat.data[15] -
        mat.data[4] * mat.data[11] * mat.data[13] -
        mat.data[8] * mat.data[5] * mat.data[15] +
        mat.data[8] * mat.data[7] * mat.data[13] +
        mat.data[12] * mat.data[5] * mat.data[11] -
        mat.data[12] * mat.data[7] * mat.data[9];

    inv.data[12] = -mat.data[4] * mat.data[9] * mat.data[14] +
        mat.data[4] * mat.data[10] * mat.data[13] +
        mat.data[8] * mat.data[5] * mat.data[14] -
        mat.data[8] * mat.data[6] * mat.data[13] -
        mat.data[12] * mat.data[5] * mat.data[10] +
        mat.data[12] * mat.data[6] * mat.data[9];

    inv.data[1] = -mat.data[1] * mat.data[10] * mat.data[15] +
        mat.data[1] * mat.data[11] * mat.data[14] +
        mat.data[9] * mat.data[2] * mat.data[15] -
        mat.data[9] * mat.data[3] * mat.data[14] -
        mat.data[13] * mat.data[2] * mat.data[11] +
        mat.data[13] * mat.data[3] * mat.data[10];

    inv.data[5] = mat.data[0] * mat.data[10] * mat.data[15] -
        mat.data[0] * mat.data[11] * mat.data[14] -
        mat.data[8] * mat.data[2] * mat.data[15] +
        mat.data[8] * mat.data[3] * mat.data[14] +
        mat.data[12] * mat.data[2] * mat.data[11] -
        mat.data[12] * mat.data[3] * mat.data[10];

    inv.data[9] = -mat.data[0] * mat.data[9] * mat.data[15] +
        mat.data[0] * mat.data[11] * mat.data[13] +
        mat.data[8] * mat.data[1] * mat.data[15] -
        mat.data[8] * mat.data[3] * mat.data[13] -
        mat.data[12] * mat.data[1] * mat.data[11] +
        mat.data[12] * mat.data[3] * mat.data[9];

    inv.data[13] = mat.data[0] * mat.data[9] * mat.data[14] -
        mat.data[0] * mat.data[10] * mat.data[13] -
        mat.data[8] * mat.data[1] * mat.data[14] +
        mat.data[8] * mat.data[2] * mat.data[13] +
        mat.data[12] * mat.data[1] * mat.data[10] -
        mat.data[12] * mat.data[2] * mat.data[9];

    inv.data[2] = mat.data[1] * mat.data[6] * mat.data[15] -
        mat.data[1] * mat.data[7] * mat.data[14] -
        mat.data[5] * mat.data[2] * mat.data[15] +
        mat.data[5] * mat.data[3] * mat.data[14] +
        mat.data[13] * mat.data[2] * mat.data[7] -
        mat.data[13] * mat.data[3] * mat.data[6];

    inv.data[6] = -mat.data[0] * mat.data[6] * mat.data[15] +
        mat.data[0] * mat.data[7] * mat.data[14] +
        mat.data[4] * mat.data[2] * mat.data[15] -
        mat.data[4] * mat.data[3] * mat.data[14] -
        mat.data[12] * mat.data[2] * mat.data[7] +
        mat.data[12] * mat.data[3] * mat.data[6];

    inv.data[10] = mat.data[0] * mat.data[5] * mat.data[15] -
        mat.data[0] * mat.data[7] * mat.data[13] -
        mat.data[4] * mat.data[1] * mat.data[15] +
        mat.data[4] * mat.data[3] * mat.data[13] +
        mat.data[12] * mat.data[1] * mat.data[7] -
        mat.data[12] * mat.data[3] * mat.data[5];

    inv.data[14] = -mat.data[0] * mat.data[5] * mat.data[14] +
        mat.data[0] * mat.data[6] * mat.data[13] +
        mat.data[4] * mat.data[1] * mat.data[14] -
        mat.data[4] * mat.data[2] * mat.data[13] -
        mat.data[12] * mat.data[1] * mat.data[6] +
        mat.data[12] * mat.data[2] * mat.data[5];

    inv.data[3] = -mat.data[1] * mat.data[6] * mat.data[11] +
        mat.data[1] * mat.data[7] * mat.data[10] +
        mat.data[5] * mat.data[2] * mat.data[11] -
        mat.data[5] * mat.data[3] * mat.data[10] -
        mat.data[9] * mat.data[2] * mat.data[7] +
        mat.data[9] * mat.data[3] * mat.data[6];

    inv.data[7] = mat.data[0] * mat.data[6] * mat.data[11] -
        mat.data[0] * mat.data[7] * mat.data[10] -
        mat.data[4] * mat.data[2] * mat.data[11] +
        mat.data[4] * mat.data[3] * mat.data[10] +
        mat.data[8] * mat.data[2] * mat.data[7] -
        mat.data[8] * mat.data[3] * mat.data[6];

    inv.data[11] = -mat.data[0] * mat.data[5] * mat.data[11] +
        mat.data[0] * mat.data[7] * mat.data[9] +
        mat.data[4] * mat.data[1] * mat.data[11] -
        mat.data[4] * mat.data[3] * mat.data[9] -
        mat.data[8] * mat.data[1] * mat.data[7] +
        mat.data[8] * mat.data[3] * mat.data[5];

    inv.data[15] = mat.data[0] * mat.data[5] * mat.data[10] -
        mat.data[0] * mat.data[6] * mat.data[9] -
        mat.data[4] * mat.data[1] * mat.data[10] +
        mat.data[4] * mat.data[2] * mat.data[9] +
        mat.data[8] * mat.data[1] * mat.data[6] -
        mat.data[8] * mat.data[2] * mat.data[5];

    double det = 1 / (mat.data[0] * inv.data[0]
        + mat.data[1] * inv.data[4]
        + mat.data[2] * inv.data[8]
        + mat.data[3] * inv.data[12]);

    for (int i = 0; i < 16; i++)
        inv.data[i] *= det;

    return inv;
}

}
