#ifndef ARCH_CAMERA_HPP
#define ARCH_CAMERA_HPP

#include <Core/Objects/Camera.hpp>
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Math/Rect.hpp"
#include "Math/Ray.hpp"


class Camera
{
public:
    Camera() = default;
    Camera(const Vector& eye, double pitch, double yaw);

    operator Core::Camera() const;

    [[nodiscard]] double getFov() const;
    [[nodiscard]] double getNear() const;
    [[nodiscard]] double getFar() const;

    [[nodiscard]] Vector getPosition() const;
    [[nodiscard]] double getPitch() const;
    [[nodiscard]] double getYaw() const;

    [[nodiscard]] Matrix getModelMatrix() const;
    [[nodiscard]] Matrix getViewMatrix() const;
    [[nodiscard]] Matrix getProjectionMatrix() const;
    [[nodiscard]] Matrix getViewProjectionMatrix() const;

    void setFov(double newFov);
    void setNear(double newNear);
    void setFar(double newFar);

    void setPosition(const Vector& newPosition);
    void setPitch(double newPitch);
    void setYaw(double newYaw);

    void translate(const Vector& offset);
    void rotate(double dPitch, double dYaw);

    Ray createRay(double x, double y, const Rect& viewport) const;

    Vector project(const Vector& point, const Rect& viewport) const;

private:
    double fov = 1.2217;
    double near = 80.0;
    double far = 1000.0;

    Vector eye;
    double pitch = 0.0;
    double yaw = 0.0;
};

#endif // ARCH_CAMERA_HPP
