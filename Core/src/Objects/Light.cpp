#include "Core/Objects/Light.hpp"

using namespace Core;


Light Core::make_ambient_light()
{
    Light light{};

    light.type = LightType::Ambient;
    light.color = Colors::white;
    light.intensity = 0.3;
    light.position = make_pos(0, 0, 0);

    return light;
}

Light Core::make_directional_light()
{
    Light light{};

    light.type = LightType::Directional;
    light.color = Colors::white;
    light.intensity = 0.7;
    light.position = make_pos(0, 0, 0);
    light.direction = normalized(make_dir(0, -4, 3));

    return light;
}

Light Core::make_directional_light(Color color, Vec direction)
{
    Light light{};

    light.type = LightType::Directional;
    light.color = color;
    light.intensity = 0.7;
    light.position = make_pos(0, 0, 0);
    light.direction = normalized(direction);

    return light;
}
