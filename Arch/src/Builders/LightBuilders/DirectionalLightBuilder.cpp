#include "Builders/DefaultIDGenerator.hpp"
#include "Builders/LightBuilders/DirectionalLightBuilder.hpp"
#include "Objects/Adapters/LightAdapter.hpp"


DirectionalLightBuilder& DirectionalLightBuilder::setColor(const Color& newColor)
{
    color = newColor;
    return *this;
}

DirectionalLightBuilder& DirectionalLightBuilder::setDirection(const Vector& newDirection)
{
    direction = newDirection;
    return *this;
}

DirectionalLightBuilder& DirectionalLightBuilder::setIntensity(double newIntensity)
{
    intensity = newIntensity;
    return *this;
}

std::unique_ptr<IObject> DirectionalLightBuilder::build()
{
    size_t id = DefaultIDGenerator().generate();
    Light light = Core::make_directional_light(color, direction.normalized());

    return std::unique_ptr<IObject>(new ObjectAdapter<Light>(id, light));
}
