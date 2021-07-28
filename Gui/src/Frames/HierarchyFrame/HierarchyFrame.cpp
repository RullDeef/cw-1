#include <QLayout>
#include "Frames/HierarchyFrame/ObjectListItemWidget/ObjectListItemWidget.hpp"
#include "Frames/HierarchyFrame/HierarchyFrame.hpp"
#include "Managers/SceneManager.hpp"
#include "Scene/Scene.hpp"


HierarchyFrame::HierarchyFrame(IManagerFactory &managerFactory, QWidget *parent)
        : IFrame(u8"Иерархия объектов", parent), managerFactory(managerFactory)
{
    setWidget(new QWidget());
    widget()->setLayout(new QVBoxLayout());

    updateHierarchy();
}

void HierarchyFrame::updateHierarchy()
{
    clearLayout(widget()->layout());

    auto scene = managerFactory.getSceneManager()->getActiveScene();
    for (auto &object : *scene)
        displayObject(object);

    auto spacer = new QSpacerItem(0, height() / 2, QSizePolicy::Fixed, QSizePolicy::Expanding);
    widget()->layout()->addItem(spacer);
}

void HierarchyFrame::displayObject(std::shared_ptr<IObject> object)
{
    auto listItem = new ObjectListItemWidget();
    listItem->setObject(object);
    //connect(listItem, &ObjectListItemWidget::selectionToggled, this, &HierarchyWidget::itemSelectionToggled);

    widget()->layout()->addWidget(listItem);
}

void HierarchyFrame::clearLayout(QLayout *layout)
{
    if (layout == nullptr)
        return;

    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        delete item;
        continue;

        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (QSpacerItem *spacerItem = item->spacerItem())
            delete spacerItem;
        if (item->widget())
            delete item->widget();
        delete item;
    }
}
