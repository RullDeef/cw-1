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
    if (newDirection.is_zero() || newDirection.getW() != 0.0)
        throw std::runtime_error("bad direction");

    direction = newDirection.normalized();
    return *this;
}

DirectionalLightBuilder& DirectionalLightBuilder::setIntensity(double newIntensity)
{
    if (newIntensity < 0.0 || newIntensity > 1.0)
        throw std::runtime_error("bad intensity");

    intensity = newIntensity;
    return *this;
}

std::unique_ptr<IObject> DirectionalLightBuilder::build()
{
    if (direction.is_zero())
        throw std::runtime_error("bad direction");

    size_t id = DefaultIDGenerator().generate();
    Light light = Core::make_directional_light(color, direction);
    light.setIntensity(intensity);

    return std::unique_ptr<IObject>(new ObjectAdapter<Light>(id, light));
}
