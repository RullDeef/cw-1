#include "Objects/IObject.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Loaders/ObjLoader/ObjLoader.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/LoadManager.hpp"


LoadManager::LoadManager(IManagerFactory& factory)
    : IManager(factory)
{
    //_loadMesh("/home/rulldeef/Projects/cw-1/Models/Wolf.obj");
}

void LoadManager::_loadMesh(const std::string& filename)
{
    std::shared_ptr<IObject> mesh = ObjLoader(filename).loadObject();

    // needs to be in scene manager
    std::shared_ptr<Scene> scene = getFactory().getSceneManager()->getActiveScene();
    scene->insert(scene->end(), mesh);
}
