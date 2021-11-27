#include "Builders/SceneBuidler.hpp"
#include "Scene/Scene.hpp"
#include <stdexcept>


SceneBuilder& SceneBuilder::prepare()
{
    scene = std::make_unique<Scene>();
    return *this;
}

SceneBuilder& SceneBuilder::addObject(std::shared_ptr<IObject> object)
{
    if (!scene)
        throw std::runtime_error("scene is not initialized");
    scene->insert(scene->end(), object);
    return *this;
}

std::unique_ptr<Scene> SceneBuilder::build()
{
    return std::move(scene);
}
