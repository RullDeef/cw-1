#include "ObjectView.hpp"
#include <QHeaderView>
#include <QItemDelegate>
#include <Frames/HierarchyFrame/CheckBoxDelegate/CheckBoxDelegate.hpp>

ObjectView::ObjectView(QWidget *parent) : QTableView(parent)
{
    horizontalHeader()->setVisible(false);
    verticalHeader()->setVisible(false);

    setItemDelegateForColumn(1, new CheckBoxDelegate());
    setItemDelegateForColumn(2, new CheckBoxDelegate());
}
