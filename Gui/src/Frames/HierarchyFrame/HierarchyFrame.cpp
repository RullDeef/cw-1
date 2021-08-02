#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "Managers/SceneManager.hpp"
#include "Frames/HierarchyFrame/ObjectView/ObjectView.hpp"
#include "ItemModels/ObjectModel.hpp"


HierarchyFrame::HierarchyFrame(IManagerFactory &managerFactory, QWidget *parent)
        : IFrame(u8"Иерархия объектов", parent), managerFactory(managerFactory)
{
    objectView = new ObjectView();
    setWidget(objectView);
}

void HierarchyFrame::updateHierarchy()
{
    auto scene = managerFactory.getSceneManager()->getActiveScene();

    delete objectModel;
    objectModel = new ObjectModel(scene);

    objectView->setModel(objectModel);
    objectView->update();
}
