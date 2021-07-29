#ifndef VEC_HPP
#define VEC_HPP


namespace Core
{
    struct Vec
    {
        double x;
        double y;
        double z;
        double w;
    };

    inline Vec make_pos(double x = 0.0, double y = 0.0, double z = 0.0, double w = 1.0);
    inline Vec make_dir(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0);

    inline double length(const Vec& vec);

    inline bool is_zero(const Vec& vec);

    inline Vec normalised(const Vec& vec);
    inline void normalise(Vec& vec);

    inline double dot(const Vec& v1, const Vec& v2);
    inline Vec cross(const Vec& v1, const Vec& v2);

    inline Vec operator+(const Vec& v1, const Vec& v2);
    inline Vec operator-(const Vec& v1, const Vec& v2);
    inline Vec operator*(double val, const Vec& vec);
    inline Vec operator*(const Vec& vec, double val);
    inline Vec operator/(const Vec& vec, double val);
    inline Vec operator-(const Vec& vec);
}

#include "VecImp.hpp"

#endif // VEC_HPP
