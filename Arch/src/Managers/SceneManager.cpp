#include <utility>
#include <algorithm>
#include <stdexcept>
#include <Builders/SceneBuidler.hpp>
#include <Objects/Mesh.hpp>
#include <Builders/BaseMeshBuilder.hpp>
#include <Objects/ObjectAdapter.hpp>
#include "Managers/IManagerFactory.hpp"
#include "Managers/RenderManager.hpp"
#include "Managers/SceneManager.hpp"


SceneManager::SceneManager(IManagerFactory& factory)
    : IManager(factory), activeScene(scenes.end())
{
}

void SceneManager::createEmptyScene()
{
    std::shared_ptr<Scene> scene = SceneBuilder().prepare().build();
    addScene(scene);
    setActiveScene(scene);

    // testing axes rendering
//    auto mesh = BaseMeshBuilder()
//            .pushPos(Vector(0, 0, 0, 1))
//            .pushPos(Vector(10, 0, 0, 1))
//            .pushPos(Vector(10, 1, 0, 1))
//            .linkFace(0, 1, 2)
//            .pushPos(Vector(0, 20, 0, 1))
//            .pushPos(Vector(0, 20, 2, 1))
//            .linkFace(0, 3, 4)
//            .pushPos(Vector(0, 0, 30, 1))
//            .pushPos(Vector(3, 0, 30, 1))
//            .linkFace(0, 5, 6)
//            .build();
//    auto adapter = std::shared_ptr<IObject>(new ObjectAdapter<Mesh>(100, std::move(mesh)));
//    addObject(adapter);
}

void SceneManager::addScene(const std::shared_ptr<Scene>& scene)
{
    scenes.push_back(scene);
    onAddScene(scene);
}

void SceneManager::removeScene(const std::shared_ptr<Scene>& scene)
{
    if (std::find(scenes.begin(), scenes.end(), scene) != scenes.end())
    {
        onBeforeRemoveScene(scene);
        scenes.remove(scene);
    }
}

void SceneManager::setActiveScene(const std::shared_ptr<Scene>& scene)
{
    auto iter = std::find(scenes.begin(), scenes.end(), scene);
    if (iter != scenes.end())
    {
        activeScene = iter;
        onActiveSceneChange(scene);
    }
}

Scene& SceneManager::getActiveScene()
{
    if (activeScene == scenes.end())
        throw std::runtime_error("bad scene pointer");
    return **activeScene;
}

std::shared_ptr<Scene> SceneManager::getActiveScenePtr()
{
    if (activeScene == scenes.end())
        throw std::runtime_error("bad shared scene pointer");
    return *activeScene;
}

void SceneManager::addObject(const std::shared_ptr<IObject>& object)
{
    Scene& scene = getActiveScene();
    scene.insert(scene.end(), object);
    onAddObject(object);
}

void SceneManager::removeObject(std::shared_ptr<IObject> object)
{
    Scene& scene = getActiveScene();
    auto iter = std::find(scene.begin(), scene.end(), object);
    if (iter != scene.end())
    {
        onBeforeRemoveObject(object);
        scene.erase(iter);
    }
}

void SceneManager::removeObject(size_t objectId)
{
    Scene& scene = getActiveScene();
    auto iter = std::find_if(scene.begin(), scene.end(),
     [objectId](const std::shared_ptr<IObject>& obj) { return obj->getId() == objectId; });
    if (iter != scene.end())
    {
        onBeforeRemoveObject(*iter);
        scene.erase(iter);
    }
}

void SceneManager::onAddScene(std::shared_ptr<Scene> scene)
{
}

void SceneManager::onBeforeRemoveScene(std::shared_ptr<Scene> scene)
{
}

void SceneManager::onActiveSceneChange(std::shared_ptr<Scene> scene)
{
    getFactory().getRenderManager()->renderActiveScene();
}

void SceneManager::onAddObject(std::shared_ptr<IObject> object)
{
    getFactory().getRenderManager()->renderActiveScene();
}

void SceneManager::onBeforeRemoveObject(std::shared_ptr<IObject> object)
{
    getFactory().getRenderManager()->renderActiveScene();
}

void SceneManager::triggerSceneChanged()
{
    onActiveSceneChange(*activeScene);
}
