#include <Managers/QtSceneManager.hpp>
#include <Managers/QtSelectionManager.hpp>
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "Managers/SceneManager.hpp"
#include "Frames/HierarchyFrame/ObjectView/ObjectView.hpp"
#include "ItemModels/ObjectModel.hpp"


HierarchyFrame::HierarchyFrame(IManagerFactory &managerFactory, QWidget *parent)
        : IFrame("Object hierarchy", parent), managerFactory(managerFactory)
{
    objectModel = new ObjectModel(managerFactory);
    objectView = new ObjectView();
    objectView->setModel(objectModel);
    setWidget(objectView);
}
