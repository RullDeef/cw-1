#include "Objects/Camera.hpp"


Camera::Camera(const Vector &eye, double pitch, double yaw)
    : eye(eye), pitch(pitch), yaw(yaw)
{
}

Camera::operator Core::Camera() const
{
    auto cam = Core::make_camera(fov, near, far);

    cam.eye = eye;
    cam.pitch = pitch;
    cam.yaw = yaw;

    Core::update_transformation(cam);
    return cam;
}

double Camera::getFov() const
{
    return fov;
}

double Camera::getNear() const
{
    return near;
}

double Camera::getFar() const
{
    return far;
}

Vector Camera::getPosition() const
{
    return eye;
}

double Camera::getPitch() const
{
    return pitch;
}

double Camera::getYaw() const
{
    return yaw;
}

Matrix Camera::getModelMatrix() const
{
    Matrix res = Matrix::fpsModel(eye, pitch, yaw);
    return res;
}

Matrix Camera::getViewMatrix() const
{
    return getModelMatrix().inverse();
}

Matrix Camera::getProjectionMatrix() const
{
    Matrix res = Matrix::perspective(fov, near, far);
    return res;
}

Matrix Camera::getViewProjectionMatrix() const
{
    return getProjectionMatrix() * getViewMatrix();
}

void Camera::setFov(double newFov)
{
    fov = newFov; ///TODO: perform checks
}

void Camera::setNear(double newNear)
{
    near = newNear; ///TODO: perform checks
}

void Camera::setFar(double newFar)
{
    far = newFar; ///TODO: perform checks
}

void Camera::setPosition(const Vector& newPosition)
{
    eye = newPosition;
}

void Camera::setPitch(double newPitch)
{
    pitch = newPitch;
}

void Camera::setYaw(double newYaw)
{
    yaw = newYaw;
}

void Camera::translate(const Vector& offset)
{
    //eye += getModelMatrix() * offset;
    eye += offset;
}

void Camera::rotate(double dPitch, double dYaw)
{
    pitch += dPitch;
    yaw += dYaw;

    if (pitch < -M_PI_2)
        pitch = -M_PI_2;

    if (pitch > M_PI_2)
        pitch = M_PI_2;
}

Ray Camera::createRay(double x, double y, const Rect& viewport) const
{
    double z = -1.0 / std::tan(fov / 2);
    auto dir = Vector(x, y, z, 0.0).normalized();

    dir = getModelMatrix() * dir;

    return Ray(eye, dir, this, viewport);
}

Vector Camera::project(const Vector& point, const Rect& viewport) const
{
    Vector res = getViewProjectionMatrix() * point;
    res.perspective_adjust();
    res = viewport.fitIn(res);
    return res;
}
