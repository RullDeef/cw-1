#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP

#include <Objects/IObject.hpp>
#include "Managers/IManager.hpp"

class IObjectVisitor;


class ObjectManager : public IManager
{
public:
    explicit ObjectManager(IManagerFactory& managerFactory);

    virtual ~ObjectManager() = default;

    void setResetBeforeToggle(bool value);

    virtual void toggleSelection(int x, int y);
    virtual void clearSelection();
    virtual void invertSelection();
    virtual void selectAll();

    virtual void applyVisitor(IObjectVisitor& visitor);

protected:
    std::shared_ptr<IObject> rayCast(int x, int y);

private:
    bool resetBeforeToggle = true;
};

#endif // OBJECTMANAGER_HPP
