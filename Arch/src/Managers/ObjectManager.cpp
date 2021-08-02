#include <Core/common/math/Ray.hpp>
#include "Managers/IManagerFactory.hpp"
#include "Managers/ObjectManager.hpp"
#include "Managers/CameraManager.hpp"
#include "Managers/SceneManager.hpp"


ObjectManager::ObjectManager(IManagerFactory &managerFactory) : IManager(managerFactory)
{
}

void ObjectManager::setResetBeforeToggle(bool value)
{
    resetBeforeToggle = value;
}

void ObjectManager::toggleSelection(int x, int y)
{
    if (resetBeforeToggle)
        clearSelection();

    auto closestObject = rayCast(x, y);
    if (closestObject)
        closestObject->setSelected(true);
}

void ObjectManager::clearSelection()
{
    auto scene = getFactory().getSceneManager()->getActiveScene();
    for (auto& object : *scene)
        object->setSelected(false);
}

void ObjectManager::invertSelection()
{
    auto scene = getFactory().getSceneManager()->getActiveScene();
    for (auto& object : *scene)
        object->setSelected(!object->isSelected());
}

void ObjectManager::selectAll()
{
    auto scene = getFactory().getSceneManager()->getActiveScene();
    for (auto& object : *scene)
        object->setSelected(true);
}

void ObjectManager::applyVisitor(IObjectVisitor &visitor)
{
    auto scene = getFactory().getSceneManager()->getActiveScene();
    for (auto& object : *scene)
        if (object->isSelected())
            object->accept(visitor);
}

std::shared_ptr<IObject> ObjectManager::rayCast(int x, int y)
{
    double tMin = std::numeric_limits<double>::infinity();
    std::shared_ptr<IObject> closestObject = nullptr;

    Core::Ray ray = getFactory().getCameraManager()->createRay(x, y);
    auto scene = getFactory().getSceneManager()->getActiveScene();
    for (auto& object : *scene)
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
