#ifndef HEIRARCHYFRAME_HPP
#define HEIRARCHYFRAME_HPP

#include <list>
#include <ItemModels/ObjectModel.hpp>
#include <Frames/HierarchyFrame/ObjectView/ObjectView.hpp>
#include "Managers/IManagerFactory.hpp"
#include "Frames/IFrame.hpp"
#include "Objects/IObject.hpp"


class HierarchyFrame : public IFrame
{
    Q_OBJECT

public:
    explicit HierarchyFrame(IManagerFactory& managerFactory, QWidget* parent = nullptr);
    virtual ~HierarchyFrame() = default;

protected slots:
    void sceneChangedSlot();

    void updateHierarchy();

protected:
    void displayObject(std::shared_ptr<IObject> object);

private:
    IManagerFactory& managerFactory;

    ObjectModel* objectModel = nullptr;
    ObjectView* objectView = nullptr;
};

#endif // HEIRARCHYFRAME_HPP
