#include <Managers/QtSceneManager.hpp>
#include <Managers/QtSelectionManager.hpp>
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

    auto sceneManager = dynamic_cast<QtSceneManager*>(managerFactory.getSceneManager().get());
    auto selectionManager = dynamic_cast<QtSelectionManager*>(managerFactory.getSelectionManager().get());

    connect(sceneManager, &QtSceneManager::activeSceneChangeSignal, this, &HierarchyFrame::sceneChangedSlot);
    connect(sceneManager, &QtSceneManager::addObjectSignal, this, &HierarchyFrame::sceneChangedSlot);
    connect(selectionManager, &QtSelectionManager::selectionChangedSignal, this, &HierarchyFrame::sceneChangedSlot);
}

void HierarchyFrame::sceneChangedSlot()
{
    updateHierarchy();
}

void HierarchyFrame::updateHierarchy()
{
    Scene& scene = managerFactory.getSceneManager()->getActiveScene();
    objectModel->setScene(scene);
    //objectView->repaint();
}
