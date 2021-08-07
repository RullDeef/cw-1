#ifndef QTSELECTIONMANAGER_HPP
#define QTSELECTIONMANAGER_HPP

#include <QObject>
#include <Managers/SelectionManager.hpp>


class QtSelectionManager : public QObject, public SelectionManager
{
    Q_OBJECT

public:
    explicit QtSelectionManager(IManagerFactory& factory);

signals:
    void selectionChangedSignal(std::list<std::shared_ptr<IObject>> selection);
    void beforeApplyVisitorSignal(std::list<std::shared_ptr<IObject>> selection);
    void applyVisitorSignal(std::list<std::shared_ptr<IObject>> selection);

protected:
    void onSelectionChanged(std::list<std::shared_ptr<IObject>> selection) override;
    void onBeforeApplyVisitor(std::list<std::shared_ptr<IObject>> selection) override;
    void onApplyVisitor(std::list<std::shared_ptr<IObject>> selection) override;
};

#endif // QTSELECTIONMANAGER_HPP
