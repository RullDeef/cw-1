#include <QApplication>
#include <QCheckBox>
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

QWidget *CheckBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)

    return new QCheckBox(parent);
}

void CheckBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto cb = qobject_cast<QCheckBox *>(editor);
    cb->setChecked(index.data().toBool());
}

void CheckBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto cb = qobject_cast<QCheckBox *>(editor);
    int value = cb->checkState() == Qt::Checked ? 1 : 0;

    model->setData(index, value, Qt::EditRole);
}

void CheckBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    QStyleOptionButton styleOptionButton;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &styleOptionButton);

    styleOptionButton.rect = option.rect;
    styleOptionButton.rect.setLeft(option.rect.x() + option.rect.width()/2 - checkbox_rect.width()/2);

    editor->setGeometry(styleOptionButton.rect);
}
