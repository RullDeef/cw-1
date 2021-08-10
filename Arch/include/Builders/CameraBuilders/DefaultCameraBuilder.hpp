#ifndef DEFAULTCAMERABUILDER_HPP
#define DEFAULTCAMERABUILDER_HPP

#include "Builders/IObjectBuilder.hpp"


class DefaultCameraBuilder : public IObjectBuilder
{
public:
    DefaultCameraBuilder();
    explicit DefaultCameraBuilder(const Vector& eye, double pitch, double yaw);

    std::unique_ptr<IObject> build() override;

private:
    Vector eye;
    double pitch;
    double yaw;
};

#endif // DEFAULTCAMERABUILDER_HPP
