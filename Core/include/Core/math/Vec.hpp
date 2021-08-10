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
    inline double inv_sqrt_fast(const Vec& vec);

    inline bool is_zero(const Vec& vec);

    inline Vec normalized(const Vec& vec);
    inline void normalize(Vec& vec);

    inline void perspective_adjust(Vec& vec);

    inline Vec interpolate(const Vec& v1, const Vec& v2, double t);

    inline double dot(const Vec& v1, const Vec& v2);
    inline Vec cross(const Vec& v1, const Vec& v2);

    inline double get(const Vec& v, int component);

    inline unsigned int bit_code(const Vec& point);

    inline Vec& operator+=(Vec& v1, const Vec& v2);
    inline Vec& operator-=(Vec& v1, const Vec& v2);
    inline Vec& operator*=(Vec& vec, double val);
    inline Vec& operator/=(Vec& vec, double val);

    inline Vec operator+(const Vec& v1, const Vec& v2);
    inline Vec operator-(const Vec& v1, const Vec& v2);
    inline Vec operator*(double val, const Vec& vec);
    inline Vec operator*(const Vec& vec, double val);
    inline Vec operator/(const Vec& vec, double val);
    inline Vec operator-(const Vec& vec);
}

#include "VecImp.hpp"

#endif // VEC_HPP