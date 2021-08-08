#include "Objects/ObjectAdapter.hpp"
#include "Scene/Scene.hpp"


Scene::Scene()
    : rawScene(Core::make_scene())
{
}

Scene::Scene(Scene &&temp) noexcept
    : objects(std::move(temp.objects)), rawScene(temp.rawScene)
{
    temp.rawScene = Core::make_scene();
}

Scene::~Scene()
{
    Core::destroy(rawScene);
}

void Scene::insert(containter_t::const_iterator pos, const std::shared_ptr<IObject> &object)
{
    objects.insert(pos, object);

    /// TODO: remove black magic
    if (auto adapter = dynamic_cast<ObjectAdapter<Mesh>*>(object.get()))
        Core::append(rawScene, Core::Mesh(adapter->getAdaptee()));
}

void Scene::erase(containter_t::const_iterator pos)
{
    objects.erase(pos);

    // TODO: update raw scene here
}

Scene::iterator Scene::begin()
{
    return objects.begin();
}

Scene::iterator Scene::end()
{
    return objects.end();
}

Scene::const_iterator Scene::begin() const
{
    return objects.begin();
}

Scene::const_iterator Scene::end() const
{
    return objects.end();
}

Core::Scene Scene::getRawScene()
{
    auto raw = Core::make_scene();

    for (auto& object : objects)
    {
        if (auto adapter = dynamic_cast<ObjectAdapter<Mesh>*>(object.get()))
            Core::append(raw, Core::Mesh(adapter->getAdaptee()));
    }

    return raw;
}
