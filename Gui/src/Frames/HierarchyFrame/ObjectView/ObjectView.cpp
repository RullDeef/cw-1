#include "ObjectView.hpp"
#include <QHeaderView>
#include <QItemDelegate>
#include <Frames/HierarchyFrame/CheckBoxDelegate/CheckBoxDelegate.hpp>

ObjectView::ObjectView(QWidget *parent) : QTableView(parent)
{
    // horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    setSelectionBehavior(SelectionBehavior::SelectRows);

    setItemDelegateForColumn(1, new CheckBoxDelegate());
    setItemDelegateForColumn(2, new CheckBoxDelegate());
}

void ObjectView::doItemsLayout()
{
    QTableView::doItemsLayout();

    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
}
