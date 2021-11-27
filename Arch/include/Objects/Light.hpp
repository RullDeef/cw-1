#ifndef ARCH_LIGHT_HPP
#define ARCH_LIGHT_HPP

#include <Core/Objects/Light.hpp>
#include "Math/Vector.hpp"
#include "Math/Color.hpp"


class Light
{
public:
    using Type = Core::LightType;

    Light() = default;

    Light(const Core::Light& light);

    operator Core::Light() const;

    [[nodiscard]] double getIntensity() const;
    [[nodiscard]] const Vector& getPosition() const;
    [[nodiscard]] const Vector& getDirection() const;
    [[nodiscard]] const Color& getColor() const;

    [[nodiscard]] Light::Type getType() const;

    void setIntensity(double newIntensity);
    void setPosition(const Vector& newPosition);
    void setDirection(const Vector& newDirection);
    void setColor(const Color& newColor);

    void setType(Light::Type newType);

private:
    Type type;

    Color color;
    Vector position;
    Vector direction;

    double intensity;
};

#endif // ARCH_LIGHT_HPP
