#ifndef DIRECTIONALLIGHTBUILDER_HPP
#define DIRECTIONALLIGHTBUILDER_HPP

#include "Math/Color.hpp"
#include "Builders/IObjectBuilder.hpp"


class DirectionalLightBuilder : public IObjectBuilder
{
public:
    DirectionalLightBuilder& setColor(const Color& newColor);
    DirectionalLightBuilder& setDirection(const Vector& newDirection);
    DirectionalLightBuilder& setIntensity(double newIntensity);

    std::unique_ptr<IObject> build() override;

private:
    Color color;
    Vector direction;
    double intensity;
};

#endif // DIRECTIONALLIGHTBUILDER_HPP
