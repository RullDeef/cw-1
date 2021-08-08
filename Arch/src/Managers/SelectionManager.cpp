#include <Core/math/Ray.hpp>
#include "Managers/IManagerFactory.hpp"
#include "Managers/SelectionManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/SceneManager.hpp"
#include "Managers/RenderManager.hpp"


SelectionManager::SelectionManager(IManagerFactory &managerFactory) : IManager(managerFactory)
{
}

void SelectionManager::setResetBeforeToggle(bool value)
{
    resetBeforeToggle = value;
}

void SelectionManager::select(std::shared_ptr<IObject> object)
{
    if (resetBeforeToggle)
        clearSelection();

    object->setSelected(true);

    onSelectionChanged(getSelectedObjects());
}

void SelectionManager::toggleSelection(int x, int y)
{
    if (resetBeforeToggle)
        clearSelection();

    auto closestObject = rayCast(x, y);
    if (closestObject)
        closestObject->setSelected(true);

    onSelectionChanged(getSelectedObjects());
}

void SelectionManager::clearSelection()
{
    setAllObjectsSelection(false);
}

void SelectionManager::selectAll()
{
    setAllObjectsSelection(true);
}

void SelectionManager::applyVisitor(IObjectVisitor &visitor)
{
    auto selected = getSelectedObjects();
    onBeforeApplyVisitor(selected);
    for (auto& object : selected)
        object->accept(visitor);
    onApplyVisitor(selected);
}

std::shared_ptr<IObject> SelectionManager::rayCast(int x, int y)
{
    auto ray = getFactory().getCameraManager()->createRay(x, y);
    Scene& scene = getFactory().getSceneManager()->getActiveScene();

    return rayCast(scene, ray);
}

std::shared_ptr<IObject> SelectionManager::rayCast(const Scene &scene, const Ray &ray)
{
    double tMin = std::numeric_limits<double>::infinity();
    std::shared_ptr<IObject> closestObject = nullptr;

    for (auto& object : scene)
    {
        double t;
        if (object->intersects(t, ray) && t < tMin)
        {
            tMin = t;
            closestObject = object;
        }
    }

    return closestObject;
}

void SelectionManager::setAllObjectsSelection(bool selected)
{
    Scene& scene = getFactory().getSceneManager()->getActiveScene();
    for (const auto& object : scene)
        object->setSelected(selected);
}

std::list<std::shared_ptr<IObject>> SelectionManager::getSelectedObjects()
{
    std::list<std::shared_ptr<IObject>> objects;

    Scene& scene = getFactory().getSceneManager()->getActiveScene();
    for (const auto& object : scene)
        if (object->isSelected())
            objects.push_back(object);

    return objects;
}

void SelectionManager::onSelectionChanged(std::list<std::shared_ptr<IObject>> selection)
{
    getFactory().getRenderManager()->renderActiveScene();
}

void SelectionManager::onBeforeApplyVisitor(std::list<std::shared_ptr<IObject>> selection)
{
}

void SelectionManager::onApplyVisitor(std::list<std::shared_ptr<IObject>> selection)
{
}
