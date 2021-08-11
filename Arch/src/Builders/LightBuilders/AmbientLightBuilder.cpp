#include "Objects/Adapters/LightAdapter.hpp"
#include "Builders/DefaultIDGenerator.hpp"
#include "Builders/LightBuilders/AmbientLightBuilder.hpp"


std::unique_ptr<IObject> AmbientLightBuilder::build()
{
    static int counter = 0;

    size_t id = DefaultIDGenerator().generate();
    Light light({});

    if (counter == 0)
        light = Core::make_ambient_light();
    else if (counter == 1)
        light = Core::make_directional_light();
    else
        light = Core::make_directional_light(Color::green(), Vector(1, -3, 2));

    auto adapter = new ObjectAdapter<Light>(id, light);
    counter = (counter + 1) % 3;
    return std::unique_ptr<IObject>(adapter);
}
