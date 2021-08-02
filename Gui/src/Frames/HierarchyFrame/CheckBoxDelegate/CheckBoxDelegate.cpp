#include <QApplication>
#include "CheckBoxDelegate.hpp"

CheckBoxDelegate::CheckBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void CheckBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool data = index.model()->data(index, Qt::DisplayRole).toBool();

    QStyleOptionButton checkBoxStyle;
    QRect checkBoxRect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkBoxStyle);

    checkBoxStyle.rect = option.rect;
    checkBoxStyle.rect.setLeft(option.rect.x() + option.rect.width()/2 - checkBoxRect.width()/2);

    if (data)
        checkBoxStyle.state = QStyle::State_On | QStyle::State_Enabled;
    else
        checkBoxStyle.state = QStyle::State_Off | QStyle::State_Enabled;

    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkBoxStyle, painter);
}
