#include "QtSelectionManager.hpp"


QtSelectionManager::QtSelectionManager(IManagerFactory &factory)
    : SelectionManager(factory)
{
}

void QtSelectionManager::onSelectionChanged(std::list<std::shared_ptr<IObject>> selection)
{
    emit selectionChangedSignal(selection);
}

void QtSelectionManager::onBeforeApplyVisitor(std::list<std::shared_ptr<IObject>> selection)
{
    emit beforeApplyVisitorSignal(selection);
}

void QtSelectionManager::onApplyVisitor(std::list<std::shared_ptr<IObject>> selection)
{
    emit applyVisitorSignal(selection);
}
