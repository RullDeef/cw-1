#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/Color.hpp"


namespace Core
{
    struct DirectionalLight
    {
        Color color;
        double intensity;
        Vec direction;
    };
}

#endif // DIRECTIONALLIGHT_HPP
