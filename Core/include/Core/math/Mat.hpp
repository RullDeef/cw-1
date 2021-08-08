#ifndef MAT_HPP
#define MAT_HPP

#include "Vec.hpp"


namespace Core
{
    struct Mat
    {
        double data[16];
    };

    inline Mat make_mat_zero();
    inline Mat make_mat_id();
    inline Mat make_mat_translation(double dx, double dy, double dz);
    inline Mat make_mat_translation(const Vec& offset);
    inline Mat make_mat_rotation(const Vec& axis, double angle);
    inline Mat make_mat_scale(double fx, double fy, double fz);
    inline Mat make_mat_scale(const Vec& factors);
    inline Mat make_mat_perspective(double fov, double near, double far);

    inline double det(const Mat& mat);
    inline Mat operator*(const Mat& left, const Mat& right);
    inline Mat operator*(const Mat& mat, double val);
    inline Mat operator*(double val, const Mat& mat);
    inline Vec operator*(const Vec& vec, const Mat& mat);
    inline Vec operator*(const Mat& mat, const Vec& vec);

    inline Mat transpose(const Mat& mat);
    inline Mat inverse(const Mat& mat);
}

#include "MatImp.hpp"

#endif // MAT_HPP
