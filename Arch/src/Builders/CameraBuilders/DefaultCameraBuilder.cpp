#include "Objects/Camera.hpp"
#include "Objects/Adapters/CameraAdapter.hpp"
#include "Builders/CameraBuilders/DefaultCameraBuilder.hpp"
#include "Builders/DefaultIDGenerator.hpp"


DefaultCameraBuilder::DefaultCameraBuilder(const Vector &eye, double pitch, double yaw)
    : eye(eye), pitch(pitch), yaw(yaw)
{
}

DefaultCameraBuilder &DefaultCameraBuilder::setId(size_t newId)
{
    id = newId;
    return *this;
}

DefaultCameraBuilder &DefaultCameraBuilder::setName(std::string newName)
{
    name = std::move(newName);
    return *this;
}

DefaultCameraBuilder &DefaultCameraBuilder::setPosition(const Vector &newPosition)
{
    if (newPosition.getW() != 1.0)
        throw std::runtime_error("bad position vector");

    position = newPosition;
    return *this;
}

DefaultCameraBuilder &DefaultCameraBuilder::setRotation(const Vector &newRotation)
{
    if (newRotation.getW() != 0.0)
        throw std::runtime_error("bad rotation vector");

    rotation = newRotation;
    return *this;
}

DefaultCameraBuilder &DefaultCameraBuilder::setScale(const Vector &newScale)
{
    if (newScale.getW() != 0.0)
        throw std::runtime_error("bad rotation vector");

    scale = newScale;
    return *this;
}

std::unique_ptr<IObject> DefaultCameraBuilder::build()
{
    Camera camera(eye, pitch, yaw);
    auto object = std::unique_ptr<IObject>(new ObjectAdapter<Camera>(id, camera));

    object->setName(name);
    object->setPosition(position);
    object->setRotation(rotation);
    object->setScale(scale);

    return object;
}
