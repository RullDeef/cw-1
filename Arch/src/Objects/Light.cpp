#include "Objects/Light.hpp"


Light::Light(const Core::Light &light)
{
    color = light.color;
    intensity = light.intensity;
    position = light.position;
    direction = light.direction;

    if (light.type == Core::LightType::Ambient)
    {
        type = Type::Ambient;
    }
    else if (light.type == Core::LightType::Directional)
    {
        type = Type::Directional;
    }
    else if (light.type == Core::LightType::Point)
    {
        type = Type::Point;
    }
}

Light::operator Core::Light() const
{
    Core::Light res{};

    res.color = color;
    res.intensity = intensity;
    res.position = position;
    res.direction = direction;

    if (type == Type::Ambient)
    {
        res.type = Core::LightType::Ambient;
    }
    else if (type == Type::Directional)
    {
        res.type = Core::LightType::Directional;
    }
    else if (type == Type::Point)
    {
        res.type = Core::LightType::Point;
    }

    return res;
}

double Light::getIntensity() const
{
    return intensity;
}

const Vector& Light::getPosition() const
{
    return position;
}

const Vector &Light::getDirection() const
{
    return direction;
}

const Color &Light::getColor() const
{
    return color;
}

Light::Type Light::getType() const
{
    return type;
}

void Light::setIntensity(double newIntensity)
{
    intensity = newIntensity;
}

void Light::setPosition(const Vector &newPosition)
{
    position = newPosition;
}

void Light::setDirection(const Vector &newDirection)
{
    direction = newDirection;
}

void Light::setColor(const Color &newColor)
{
    color = newColor;
}

void Light::setType(Light::Type newType)
{
    type = newType;
}
