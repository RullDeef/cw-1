#ifndef AMBIENTLIGHT_HPP
#define AMBIENTLIGHT_HPP

#include "Core/common/Color.hpp"


namespace Core
{
    struct AmbientLight
    {
        Color color;
        double intensity;
    };

    AmbientLight make_ambient_light();
}

#endif // AMBIENTLIGHT_HPP
