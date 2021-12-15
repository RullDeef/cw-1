#ifndef SELECTIONMANAGER_HPP
#define SELECTIONMANAGER_HPP

#include <list>
#include "Math/Ray.hpp"
#include "Objects/Camera.hpp"
#include "Objects/IObject.hpp"
#include "Scene/Scene.hpp"
#include "Managers/IManager.hpp"


class SelectionManager : public IManager
{
public:
    explicit SelectionManager(IManagerFactory& managerFactory);
    virtual ~SelectionManager() = default;

    std::list<std::shared_ptr<IObject>> getSelectedObjects();

    void setResetBeforeToggle(bool value);

    void select(std::shared_ptr<IObject> object);
    void toggleSelection(int x, int y);
    void clearSelection();

    void selectAll();
    void invertSelection();
    void applyVisitor(IObjectVisitor& visitor);

    void deleteSelected();

protected:
    virtual void onSelectionChanged(std::list<std::shared_ptr<IObject>> selection);
    virtual void onBeforeApplyVisitor(std::list<std::shared_ptr<IObject>> selection);

    virtual void onApplyVisitor(std::list<std::shared_ptr<IObject>> selection);
private:
    std::shared_ptr<IObject> rayCast(int x, int y);

    std::shared_ptr<IObject> rayCast(const Scene& scene, const Ray& ray);
    void setAllObjectsSelection(bool selected);

    bool resetBeforeToggle = true;
};

#endif // SELECTIONMANAGER_HPP
