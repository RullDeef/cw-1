#include "Objects/Light.hpp"


Light::Light(const Core::Light &light)
{
    if (light.type == Core::Light::Type::Ambient)
    {
        type = Type::Ambient;
        color = light.ambient.color;
        intensity = light.ambient.intensity;
    }
    else if (light.type == Core::Light::Type::Directional)
    {
        type = Type::Directional;
        color = light.directional.color;
        direction = light.directional.direction;
        intensity = light.directional.intensity;
    }
    else if (light.type == Core::Light::Type::Point)
    {
        type = Type::Point;
        color = light.point.color;
        position = light.point.position;
        intensity = light.point.intensity;
    }
}

Light::operator Core::Light() const
{
    Core::Light res{};

    if (type == Type::Ambient)
    {
        res.type = Core::Light::Type::Ambient;
        res.ambient.color = color;
        res.ambient.intensity = intensity;
    }
    else if (type == Type::Directional)
    {
        res.type = Core::Light::Type::Directional;
        res.directional.color = color;
        res.directional.direction = direction;
        res.directional.intensity = intensity;
    }
    else if (type == Type::Point)
    {
        res.type = Core::Light::Type::Point;
        res.point.color = color;
        res.point.position = position;
        res.point.intensity = intensity;
    }

    return res;
}

const Vector& Light::getPosition() const
{
    return position;
}
