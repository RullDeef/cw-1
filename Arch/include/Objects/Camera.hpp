#ifndef ARCH_CAMERA_HPP
#define ARCH_CAMERA_HPP

#include <Core/Objects/Camera.hpp>
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Math/Ray.hpp"


class Camera
{
public:
    Camera() = default;
    Camera(const Vector& eye, double pitch, double yaw);

    operator Core::Camera() const;

    Vector getPosition() const;
    Matrix getModelMatrix() const;

    void translate(const Vector& offset);
    void rotate(double dPitch, double dYaw);

    Ray createRay(double x, double y) const;

private:
    double fov = 1.2217;
    double near = 80.0;
    double far = 1000.0;

    Vector eye;
    double pitch = 0.0;
    double yaw = 0.0;
};

#endif // ARCH_CAMERA_HPP
