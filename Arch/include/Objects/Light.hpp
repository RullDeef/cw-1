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
    [[nodiscard]] const Vector& getAttenuation() const;
    [[nodiscard]] double getRadius() const;

    [[nodiscard]] Light::Type getType() const;

    void setIntensity(double newIntensity);
    void setPosition(const Vector& newPosition);
    void setDirection(const Vector& newDirection);
    void setColor(const Color& newColor);
    void setAttenuation(const Vector& newAttenuation);
    void setRadius(double newRadius);
    void setOutline(bool newOutline);
    void setVisible(bool newVisible);

    void setType(Light::Type newType);

private:
    Type type = Core::LightType::Ambient;

    Color color = Color::white();
    double intensity = 1.0;

    Vector position = Vector(0, 0, 0, 1);
    Vector direction = Vector(1, 0, 0, 0);
    Vector attenuation = Vector(1, 0, 0, 0);
    double radius = 1.0;

    bool outline = false;
    bool visible = true;
};

#endif // ARCH_LIGHT_HPP
