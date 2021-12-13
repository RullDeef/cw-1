#include "Core/Objects/Light.hpp"

using namespace Core;

Light Core::make_ambient_light(Color color, double intensity)
{
    Light light{};

    light.type = LightType::Ambient;
    light.color = color;
    light.intensity = intensity;
    light.position = make_pos(0, 0, 0);
    light.direction = make_dir(1, 0, 0);
    light.attenuation = make_dir(1, 0, 1);
    light.radius = 1.0;

    return light;
}

Light Core::make_directional_light(Color color, double intensity, Vec direction)
{
    Light light{};

    light.type = LightType::Directional;
    light.color = color;
    light.intensity = intensity;
    light.position = make_pos(0, 0, 0);
    light.direction = normalized(direction);
    light.attenuation = make_dir(1, 0, 1);
    light.radius = 1.0;

    return light;
}

Light Core::make_point_light(Color color, double intensity, Vec position, Vec attenuation, double radius)
{
    Light light{};

    light.type = LightType::Point;
    light.color = color;
    light.intensity = intensity;
    light.position = position;
    light.direction = make_dir(1, 0, 0);
    light.attenuation = attenuation;
    light.radius = radius;

    return light;
}
