#include "Managers/QtSelectionManager.hpp"
#include "InspectorFrame.hpp"
#include <Managers/RenderManager.hpp>
#include <Managers/SceneManager.hpp>


InspectorFrame::InspectorFrame(IManagerFactory &managerFactory, QWidget *parent)
    : IFrame("Inspector", parent), managerFactory(&managerFactory), inspectorWidget(new InspectorWidget())
{
    setWidget(inspectorWidget);

    auto selectionManager = dynamic_cast<QtSelectionManager*>(managerFactory.getSelectionManager().get());
    connect(selectionManager, &QtSelectionManager::selectionChangedSignal, this, &InspectorFrame::updateInspectee);
    connect(inspectorWidget, &InspectorWidget::objectChangedSignal, this, &InspectorFrame::objectChanged);
}

void InspectorFrame::updateInspectee()
{
    auto selection = managerFactory->getSelectionManager()->getSelectedObjects();

    if (selection.size() != 1)
        inspectorWidget->inspect(nullptr);
    else
        inspectorWidget->inspect(selection.front());
}

void InspectorFrame::objectChanged()
{
    managerFactory->getSceneManager()->triggerSceneChanged();
}
