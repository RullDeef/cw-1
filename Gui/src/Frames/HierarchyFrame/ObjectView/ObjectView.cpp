#include <QHeaderView>
#include <QItemDelegate>
#include "Frames/HierarchyFrame/CheckBoxDelegate/CheckBoxDelegate.hpp"
#include "ObjectView.hpp"


ObjectView::ObjectView(QWidget *parent) : QTableView(parent)
{
    verticalHeader()->setVisible(false);

    setSelectionBehavior(SelectionBehavior::SelectRows);

    setItemDelegateForColumn(1, new CheckBoxDelegate());
    setItemDelegateForColumn(2, new CheckBoxDelegate());
}

void ObjectView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    QTableView::selectionChanged(selected, deselected);

    for (const auto& range : selected)
        model()->setData(range.indexes().value(0), true);
    for (const auto& range : deselected)
        model()->setData(range.indexes().value(0), false);
}

void ObjectView::doItemsLayout()
{
    QTableView::doItemsLayout();

    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
}
