#include "Vec.hpp"
#include <cmath>


namespace Core
{

inline Vec make_pos(double x, double y, double z, double w)
{
    return Vec { x, y, z, w };
}

inline Vec make_dir(double x, double y, double z, double w)
{
    return Vec { x, y, z, w };
}

inline double length(const Vec& vec)
{
    return std::hypot(vec.x, vec.y, vec.z);
}

inline Vec normalised(const Vec& vec)
{
    double f = 1.0 / length(vec);
    return make_dir(f * vec.x, f * vec.y, f * vec.z, vec.w);
}

inline void normalize(Vec& vec)
{
    vec = normalised(vec);
}

inline double dot(const Vec& v1, const Vec& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vec cross(const Vec& v1, const Vec& v2)
{
    Vec res{};

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    res.w = 0.0;

    return res;
}

inline Vec operator+(const Vec& v1, const Vec& v2)
{
    return make_pos(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}

inline Vec operator-(const Vec& v1, const Vec& v2)
{
    return make_pos(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}

inline Vec operator*(double val, const Vec& vec)
{
    return make_dir(val * vec.x, val * vec.y, val * vec.z, val * vec.w);
}

inline Vec operator*(const Vec& vec, double val)
{
    return val * vec;
}

inline Vec operator/(const Vec& vec, double val)
{
    return (1.0 / val) * vec;
}

inline Vec operator-(const Vec& vec)
{
    return make_dir(-vec.x, -vec.y, -vec.z, vec.w);
}

}
