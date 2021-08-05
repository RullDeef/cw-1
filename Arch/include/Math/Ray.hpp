#ifndef ARCH_RAY_HPP
#define ARCH_RAY_HPP

#include <Core/common/math/Ray.hpp>
#include "Math/Vector.hpp"

class Ray
{
public:
    Ray(const Vector& position, const Vector& direction);
    Ray(const Core::Ray& ray);

    operator Core::Ray() const;

private:
    Vector position;
    Vector direction;
};

#endif //ARCH_RAY_HPP
