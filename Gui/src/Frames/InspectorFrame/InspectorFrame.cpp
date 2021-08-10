#include "Managers/QtSelectionManager.hpp"
#include "InspectorFrame.hpp"


InspectorFrame::InspectorFrame(IManagerFactory &managerFactory, QWidget *parent)
    : IFrame("Inspector", parent), managerFactory(&managerFactory), inspectorWidget(new InspectorWidget())
{
    setWidget(inspectorWidget);

    auto selectionManager = dynamic_cast<QtSelectionManager*>(managerFactory.getSelectionManager().get());
    connect(selectionManager, &QtSelectionManager::selectionChangedSignal, this, &InspectorFrame::updateInspectee);
}

void InspectorFrame::updateInspectee()
{
    auto selection = managerFactory->getSelectionManager()->getSelectedObjects();

    if (selection.size() != 1)
        inspectorWidget->inspect(nullptr);
    else
        inspectorWidget->inspect(selection.front());
}

