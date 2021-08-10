#ifndef ARCH_LIGHT_HPP
#define ARCH_LIGHT_HPP

#include <Core/Objects/Light.hpp>
#include "Math/Vector.hpp"
#include "Math/Color.hpp"


class Light
{
    enum class Type
    {
        Ambient,
        Directional,
        Point
    };

public:
    Light(const Core::Light& light);

    operator Core::Light() const;

    [[nodiscard]] const Vector& getPosition() const;
    [[nodiscard]] const Vector& getDirection() const;

    void setPosition(const Vector& newPosition);
    void setDirection(const Vector& newDirection);

private:
    Type type;

    Color color;
    Vector position;
    Vector direction;

    double intensity;
};

#endif // ARCH_LIGHT_HPP
