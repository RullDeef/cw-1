#ifndef DEFAULTCAMERABUILDER_HPP
#define DEFAULTCAMERABUILDER_HPP

#include "Builders/IObjectBuilder.hpp"


class DefaultCameraBuilder : public IObjectBuilder
{
public:
    DefaultCameraBuilder() = default;
    explicit DefaultCameraBuilder(const Vector& eye, double pitch, double yaw);

    DefaultCameraBuilder& setId(size_t newId);
    DefaultCameraBuilder& setName(std::string newName);
    DefaultCameraBuilder& setPosition(const Vector& newPosition);
    DefaultCameraBuilder& setRotation(const Vector& newRotation);
    DefaultCameraBuilder& setScale(const Vector& newScale);

    std::unique_ptr<IObject> build() override;

private:
    Vector eye = Vector(0, 20, 30, 1);
    double pitch = -atan2(20, 30);
    double yaw = 0.0;

    size_t id = 0;
    std::string name;
    Vector position = Vector(0, 0, 0, 1);
    Vector rotation = Vector(0, 0, 0, 0);
    Vector scale = Vector(1, 1, 1, 0);
};

#endif // DEFAULTCAMERABUILDER_HPP
