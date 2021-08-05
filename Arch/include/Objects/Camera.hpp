#ifndef ARCH_CAMERA_HPP
#define ARCH_CAMERA_HPP

#include "Core/Objects/Camera.hpp"


class Camera
{
public:
    Camera() = default;

    operator Core::Camera() const;

    /// TODO: implement
};

#endif // ARCH_CAMERA_HPP
