#include "Vec.hpp"
#include <cmath>
#include <cstdint>


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

    inline double inv_sqrt_fast(const Vec& vec)
    {
        float number = dot(vec, vec);
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

    inline bool is_zero(const Vec& vec)
    {
        return vec.x == std::numeric_limits<double>::epsilon()
            && vec.y == std::numeric_limits<double>::epsilon()
            && vec.z == std::numeric_limits<double>::epsilon();
    }

    inline Vec normalized(const Vec& vec)
    {
        /// TODO: pref tests
        double f = 1.0 / length(vec); // inv_sqrt_fast(vec);
        return make_dir(f * vec.x, f * vec.y, f * vec.z, vec.w);
    }

    inline void normalize(Vec& vec)
    {
        vec = normalized(vec);
    }

    inline void perspective_adjust(Vec& vec)
    {
        vec.x /= vec.w;
        vec.y /= vec.w;
        vec.z /= vec.w;
        vec.w = 1.0;
    }

    inline Vec interpolate(const Vec& v1, const Vec& v2, double t)
    {
        return (1.0 - t) * v1 + t * v2;
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

    inline double get(const Vec& v, int component)
    {
        if (component == 0)
            return v.x;
        else if (component == 1)
            return v.y;
        else if (component == 2)
            return v.z;
        else if (component == 3)
            return v.w;
        else
            return 0.0;
    }

    inline unsigned int bit_code(const Vec& point)
    {
        unsigned int code = 0x000000;

        code |= (point.x < -point.w ? 1 : 0) << 0;
        code |= (point.x >  point.w ? 1 : 0) << 1;
        code |= (point.y < -point.w ? 1 : 0) << 2;
        code |= (point.y >  point.w ? 1 : 0) << 3;
        code |= (point.z < -point.w ? 1 : 0) << 4;
        code |= (point.z >  point.w ? 1 : 0) << 5;

        return code;
    }

    inline Vec& operator+=(Vec& v1, const Vec& v2)
    {
        v1 = v1 + v2;
        return v1;
    }

    inline Vec& operator-=(Vec& v1, const Vec& v2)
    {
        v1 = v1 - v2;
        return v1;
    }

    inline Vec& operator*=(Vec& vec, double val)
    {
        vec = vec * val;
        return vec;
    }

    inline Vec& operator/=(Vec& vec, double val)
    {
        vec = vec / val;
        return vec;
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
