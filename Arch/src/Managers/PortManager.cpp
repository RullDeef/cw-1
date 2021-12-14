#include "Managers/PortManager.hpp"
#include "Importers/UdfImporter/UdfImporter.hpp"
#include "Exporters/UdfEXporter/UdfExporter.hpp"
#include "Managers/IManagerFactory.hpp"
#include "Managers/SceneManager.hpp"
#include <fstream>
#include <Loaders/ObjLoader/ObjLoader.hpp>
#include <Objects/ObjectAdapter.hpp>
#include <Builders/BaseMeshBuilder.hpp>
#include <Builders/NameGenerator.hpp>
#include "Managers/SelectionManager.hpp"

PortManager::PortManager(IManagerFactory& factory) : IManager(factory)
 {
 }

void PortManager::importScene()
{
    auto filename = requestFilename();

    std::ifstream stream(filename);
    auto scene = UdfImporter().importScene(stream);

    beforeSceneImport(filename, scene);
    getFactory().getSceneManager()->addScene(scene);
    getFactory().getSceneManager()->setActiveScene(scene);
    onSceneImport(filename, scene);
}

void PortManager::importMesh()
{
    std::string filename = requestFilename();
    std::shared_ptr<IObject> object = ObjLoader().loadMesh(filename);

    auto& scene = getFactory().getSceneManager()->getActiveScene();
    auto newName = NameGenerator::uniqueIndexedName(object->getName(), scene);
    object->setName(newName);

    getFactory().getSceneManager()->addObject(object);
    getFactory().getSelectionManager()->select(object);

    onObjectImport(filename, object);
}

void PortManager::importCamera()
{
    throw std::runtime_error("not implemented");
}

void PortManager::importLight()
{
    throw std::runtime_error("not implemented");
}

void PortManager::exportScene()
{
    auto scene = getFactory().getSceneManager()->getActiveScenePtr();
    auto filename = requestFilename();

    beforeSceneExport(filename, scene);
    std::ofstream stream(filename);
    UdfExporter().exportScene(stream, scene);
    onSceneExport(filename, scene);
}

void PortManager::beforeSceneImport(const std::string& filename, std::shared_ptr<Scene> scene) {}
void PortManager::onSceneImport(const std::string& filename, std::shared_ptr<Scene> scene) {}

void PortManager::beforeObjectImport(const std::string& filename, std::shared_ptr<IObject> object) {}
void PortManager::onObjectImport(const std::string& filename, std::shared_ptr<IObject> object) {}

void PortManager::beforeSceneExport(const std::string& filename, std::shared_ptr<Scene> scene) {}
void PortManager::onSceneExport(const std::string& filename, std::shared_ptr<Scene> scene) {}
