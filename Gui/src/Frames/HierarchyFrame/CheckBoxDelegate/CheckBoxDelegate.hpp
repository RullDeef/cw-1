#ifndef CHECKBOXDELEGATE_HPP
#define CHECKBOXDELEGATE_HPP

#include <QStyledItemDelegate>


class CheckBoxDelegate : public QStyledItemDelegate
{
public:
    explicit CheckBoxDelegate(QObject* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};


#endif // CHECKBOXDELEGATE_HPP
