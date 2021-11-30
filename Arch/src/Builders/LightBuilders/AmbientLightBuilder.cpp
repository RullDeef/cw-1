#include "Builders/DefaultIDGenerator.hpp"
#include "Builders/LightBuilders/AmbientLightBuilder.hpp"
#include "Objects/Adapters/LightAdapter.hpp"

AmbientLightBuilder &AmbientLightBuilder::setId(size_t newId)
{
    id = newId;
    return *this;
}

AmbientLightBuilder &AmbientLightBuilder::setName(std::string newName)
{
    name = std::move(newName);
    return *this;
}

AmbientLightBuilder &AmbientLightBuilder::setPosition(const Vector &newPosition)
{
    if (newPosition.getW() != 1.0)
        throw std::runtime_error("bad position vector");

    position = newPosition;
    return *this;
}

AmbientLightBuilder &AmbientLightBuilder::setRotation(const Vector &newRotation)
{
    if (newRotation.getW() != 0.0)
        throw std::runtime_error("bad rotation vector");

    rotation = newRotation;
    return *this;
}

AmbientLightBuilder &AmbientLightBuilder::setScale(const Vector &newScale)
{
    if (newScale.getW() != 0.0)
        throw std::runtime_error("bad rotation vector");

    scale = newScale;
    return *this;
}

std::unique_ptr<IObject> AmbientLightBuilder::build()
{
    Light light = Core::make_ambient_light();

    ///TODO: add parameters to builder
    auto object = std::unique_ptr<IObject>(new ObjectAdapter<Light>(id, light));

    object->setName(name);
    object->setPosition(position);
    object->setRotation(rotation);
    object->setScale(scale);

    return object;
}
