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
    };

    using ColorComputeFn = std::function<Color(const Vec& pos, const Vec& norm, const Material& mat)>;

    Light make_ambient_light();

    Light make_directional_light();
    Light make_directional_light(Color color, Vec direction);

}

#endif // LIGHT_HPP
