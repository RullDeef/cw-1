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
}

void Scene::erase(containter_t::const_iterator pos)
{
    objects.erase(pos);
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

Scene::operator Core::Scene() const
{
    Core::clear_scene((Core::Scene&)rawScene);

    for (auto& object : objects)
    {
        if (auto adapter = dynamic_cast<ObjectAdapter<Mesh>*>(object.get()))
            Core::append((Core::Scene&)rawScene, Core::Mesh(adapter->getAdaptee()));
        else if (auto adapter = dynamic_cast<ObjectAdapter<Light>*>(object.get()))
            Core::append((Core::Scene&)rawScene, adapter->getAdaptee());
    }

    return rawScene;
}
