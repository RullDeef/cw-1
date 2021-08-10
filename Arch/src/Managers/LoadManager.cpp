#include <utility>
#include <Builders/CameraBuilders/DefaultCameraBuilder.hpp>
#include <Builders/LightBuilders/AmbientLightBuilder.hpp>
#include "Objects/IObject.hpp"
#include "Loaders/ILoader.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/LoadManager.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/SelectionManager.hpp"
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

    getFactory().getSceneManager()->addObject(object);
    getFactory().getSelectionManager()->select(object);

    onObjectLoad(object);
}

void LoadManager::loadCamera()
{
    std::string filename = requestFilename();
    std::shared_ptr<IObject> object = loader->loadCamera(filename);

    getFactory().getSceneManager()->addObject(object);

    onObjectLoad(object);
}

void LoadManager::loadLight()
{
    std::string filename = requestFilename();
    std::shared_ptr<IObject> object = loader->loadLight(filename);

    getFactory().getSceneManager()->addObject(object);

    onObjectLoad(object);
}

void LoadManager::buildCamera()
{
    std::shared_ptr<IObject> object = DefaultCameraBuilder().build();

    getFactory().getSceneManager()->addObject(object);

    onObjectLoad(object);
}

void LoadManager::buildLight()
{
    std::shared_ptr<IObject> object = AmbientLightBuilder().build();

    getFactory().getSceneManager()->addObject(object);

    onObjectLoad(object);
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
