#ifndef ARCH_RAY_HPP
#define ARCH_RAY_HPP

#include <Core/math/Ray.hpp>
#include "Math/Vector.hpp"
#include "Math/Rect.hpp"

class Camera;

class Ray
{
public:
    Ray(const Vector& position, const Vector& direction, const Camera* camera = nullptr, Rect viewport = Rect(0, 0, 0, 0));
    Ray(const Core::Ray& ray);

    operator Core::Ray() const;

    inline const Vector& getPosition() const { return position; }
    inline const Vector& getDirection() const { return direction; }
    inline const Camera* getCamera() const { return camera; }
    inline const Rect& getViewport() const { return viewport; }

    bool intersectsSphere(double& t, const Vector& center, double radius) const;
    bool intersectsPlane(double& t, const Vector& pos, const Vector& normal) const;

private:
    Vector position;
    Vector direction;

    const Camera* camera;
    Rect viewport;
};

#endif //ARCH_RAY_HPP
