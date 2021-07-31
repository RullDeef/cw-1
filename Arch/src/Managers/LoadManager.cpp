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
    getFactory().getSceneManager()->addObject(mesh);
}
