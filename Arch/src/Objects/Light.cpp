#include "Objects/Light.hpp"


Light::Light(const Core::Light &light) : color(light.color), intensity(light.intensity),
        position(light.position), direction(light.direction), type(light.type)
{}

Light::operator Core::Light() const
{
    Core::Light res{};

    res.color = color;
    res.intensity = intensity;
    res.position = position;
    res.direction = direction;
    res.type = type;

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
