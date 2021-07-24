#include "LoadManager.hpp"
#include "IManagerFactory.hpp"
#include "IObject.hpp"
#include "ObjectAdapter.hpp"
#include "Loaders/ObjLoader/ObjLoader.hpp"


LoadManager::LoadManager(IManagerFactory& factory)
    : IManager(factory)
{
    //_loadMesh("/home/rulldeef/Projects/cw-1/Models/cube.obj");
}

void LoadManager::_loadMesh(const std::string& filename)
{
    std::shared_ptr<IObject> mesh = ObjLoader(filename).loadObject();

    // needs to be in scene manager
    std::shared_ptr<Scene> scene = getFactory().getSceneManager()->getActiveScene();
    scene->insert(scene->end(), mesh);
}
