#ifndef ARCH_RAY_HPP
#define ARCH_RAY_HPP

#include <Core/math/Ray.hpp>
#include "Math/Vector.hpp"

class Ray
{
public:
    Ray(const Vector& position, const Vector& direction);
    Ray(const Core::Ray& ray);

    operator Core::Ray() const;

    bool intersectsSphere(double& t, const Vector& center, double radius) const;

private:
    Vector position;
    Vector direction;
};

#endif //ARCH_RAY_HPP
