#include "Core/Objects/Light.hpp"

using namespace Core;


AmbientLight Core::make_ambient_light()
{
    AmbientLight light{};

    light.color = Colors::white;
    light.intensity = 0.3;

    return light;
}
