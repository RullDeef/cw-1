#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <functional>
#include "Core/math/Vec.hpp"
#include "Core/common/Color.hpp"


namespace Core
{
    struct Material;

    enum class LightType
    {
        Ambient,
        Directional,
        Point
    };

    struct Light
    {
        LightType type;

        Color color;
        double intensity;

        Vec position;
        Vec direction;

        /* for point light */
        Vec attenuation;
        double radius;
    };

    using ColorComputeFn = std::function<Color(const Vec& pos, const Vec& norm, const Material& mat)>;

    ///TODO: use this functions!!!
    Light make_ambient_light(Color color, double intensity);
    Light make_directional_light(Color color, double intensity, Vec direction);
    Light make_point_light(Color color, double intensity, Vec position, Vec attenuation, double radius);
}

#endif // LIGHT_HPP
