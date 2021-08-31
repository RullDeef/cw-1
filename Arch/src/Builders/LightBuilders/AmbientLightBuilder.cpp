#include "Builders/DefaultIDGenerator.hpp"
#include "Builders/LightBuilders/AmbientLightBuilder.hpp"
#include "Objects/Adapters/LightAdapter.hpp"


std::unique_ptr<IObject> AmbientLightBuilder::build()
{
    size_t id = DefaultIDGenerator().generate();
    Light light = Core::make_ambient_light();

    return std::unique_ptr<IObject>(new ObjectAdapter<Light>(id, light));
}
