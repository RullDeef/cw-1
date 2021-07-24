#include "Scene.hpp"
#include "ObjectAdapter.hpp"


Scene::Scene()
    : rawScene(Core::make_scene())
{
}

Scene::~Scene()
{
    Core::destroy(rawScene);
}

void Scene::insert(containter_t::const_iterator pos, const std::shared_ptr<IObject> &object)
{
    objects.insert(pos, object);

    if (auto adapter = dynamic_cast<ObjectAdapter<Core::Mesh>*>(object.get()))
        Core::append(rawScene, adapter->getAdaptee());
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

Core::Scene& Scene::getRawScene()
{
    return rawScene;
}

const Core::Scene& Scene::getRawScene() const
{
    return rawScene;
}
