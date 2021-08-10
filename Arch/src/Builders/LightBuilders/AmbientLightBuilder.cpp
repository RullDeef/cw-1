#include "Objects/Adapters/LightAdapter.hpp"
#include "Builders/DefaultIDGenerator.hpp"
#include "Builders/LightBuilders/AmbientLightBuilder.hpp"


std::unique_ptr<IObject> AmbientLightBuilder::build()
{
    size_t id = DefaultIDGenerator().generate();
    Light light({ Core::Light::Type::Ambient, Core::make_ambient_light() });

    auto adapter = new ObjectAdapter<Light>(id, light);
    return std::unique_ptr<IObject>(adapter);
}
