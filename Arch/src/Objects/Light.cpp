#include "Objects/Light.hpp"


Light::Light(const Core::Light &light) : color(light.color), intensity(light.intensity), position(light.position),
    direction(light.direction), attenuation(light.attenuation), type(light.type), outline(light.outline), visible(light.visible)
{}

Light::operator Core::Light() const
{
    Core::Light res{};

    res.color = color;
    res.intensity = intensity;
    res.position = position;
    res.direction = direction;
    res.attenuation = attenuation;
    res.radius = radius;
    res.type = type;
    res.outline = outline;
    res.visible = visible;

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

const Vector& Light::getAttenuation() const
{
    return attenuation;
}

double Light::getRadius() const
{
    return radius;
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

void Light::setAttenuation(const Vector &newAttenuation)
{
    attenuation = newAttenuation;
}

void Light::setRadius(double newRadius)
{
    if (newRadius <= 0.0)
        throw std::runtime_error("bad radius"); ///TODO: add other validations
    radius = newRadius;
}

void Light::setOutline(bool newOutline)
{
    outline = newOutline;
}

void Light::setVisible(bool newVisible)
{
    visible = newVisible;
}

void Light::setType(Light::Type newType)
{
    type = newType;
}
