#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/Color.hpp"

namespace Core
{
    struct PointLight
    {
        Color color;
        double intensity;
        Vec position;
    };
}

#endif // POINTLIGHT_HPP
