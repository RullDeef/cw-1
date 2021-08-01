#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Core/Objects/AmbientLight.hpp"
#include "Core/Objects/PointLight.hpp"
#include "Core/Objects/DirectionalLight.hpp"


namespace Core
{
    struct Light
    {
        enum class Type
        {
            Ambient,
            Directional,
            Point
        };

        Type type;

        union
        {
            AmbientLight ambient;
            DirectionalLight directional;
            PointLight point;
        };
    };
}

#endif // LIGHT_HPP
