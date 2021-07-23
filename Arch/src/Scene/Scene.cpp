#include "Scene.hpp"


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
