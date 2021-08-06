#include <utility>
#include <stdexcept>
#include "Objects/IObject.hpp"
#include "Loaders/ILoader.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/LoadManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Builders/EmptySceneBuidler.hpp"


LoadManager::LoadManager(IManagerFactory& factory)
    : IManager(factory)
{
}

void LoadManager::loadEmptyScene()
{
    std::shared_ptr<Scene> scene = EmptySceneBuilder().build();

    auto sceneManager = getFactory().getSceneManager();
    sceneManager->addScene(scene);
    sceneManager->setActiveScene(scene);

    std::shared_ptr<IObject> woof = loader->loadMesh("/home/rulldeef/Projects/cw-1/Models/Wolf.obj");
    sceneManager->addObject(woof);

    onSceneLoad(scene);
}

void LoadManager::loadScene()
{
    std::string filename = requestFilename();
    std::shared_ptr<Scene> scene = loader->loadScene(filename);

    auto sceneManager = getFactory().getSceneManager();
    sceneManager->addScene(scene);
    sceneManager->setActiveScene(scene);

    onSceneLoad(scene);
}

void LoadManager::loadMesh()
{
    std::string filename = requestFilename();
    std::shared_ptr<IObject> object = loader->loadMesh(filename);

    /// may be error here (SceneManager doesnt imported)
    getFactory().getSceneManager()->addObject(object);

    onObjectLoad(object);
}

void LoadManager::loadCamera()
{
    /// TODO: implement
    throw std::runtime_error("not implemented");
}

void LoadManager::loadLight()
{
    /// TODO: implement
    throw std::runtime_error("not implemented");
}

void LoadManager::setLoader(std::shared_ptr<ILoader> newLoader)
{
    loader = std::move(newLoader);
}

void LoadManager::onSceneLoad(std::shared_ptr<Scene> scene)
{
}

void LoadManager::onObjectLoad(std::shared_ptr<IObject> object)
{
}
