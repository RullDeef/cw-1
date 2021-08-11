#include "Objects/Light.hpp"


Light::Light(const Core::Light &light)
{
    color = light.color;
    intensity = light.intensity;

    if (light.type == Core::LightType::Ambient)
    {
        type = Type::Ambient;
    }
    else if (light.type == Core::LightType::Directional)
    {
        type = Type::Directional;
        direction = light.direction;
    }
    else if (light.type == Core::LightType::Point)
    {
        type = Type::Point;
        position = light.position;
    }
}

Light::operator Core::Light() const
{
    Core::Light res{};

    res.color = color;
    res.intensity = intensity;

    if (type == Type::Ambient)
    {
        res.type = Core::LightType::Ambient;
    }
    else if (type == Type::Directional)
    {
        res.type = Core::LightType::Directional;
        res.direction = direction;
    }
    else if (type == Type::Point)
    {
        res.type = Core::LightType::Point;
        res.position = position;
    }

    return res;
}

const Vector& Light::getPosition() const
{
    return position;
}

const Vector &Light::getDirection() const
{
    return direction;
}

void Light::setPosition(const Vector &newPosition)
{
    position = newPosition;
}

void Light::setDirection(const Vector &newDirection)
{
    direction = newDirection;
}
