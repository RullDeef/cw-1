#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "Managers/SceneManager.hpp"
#include "Frames/HierarchyFrame/ObjectView/ObjectView.hpp"
#include "ItemModels/ObjectModel.hpp"


HierarchyFrame::HierarchyFrame(IManagerFactory &managerFactory, QWidget *parent)
        : IFrame(u8"Иерархия объектов", parent), managerFactory(managerFactory)
{
    objectModel = new ObjectModel();
    objectView = new ObjectView();
    objectView->setModel(objectModel);
    setWidget(objectView);
}

void HierarchyFrame::updateHierarchy()
{
    Scene& scene = managerFactory.getSceneManager()->getActiveScene();
    objectModel->setScene(scene);
    //objectView->repaint();
}
