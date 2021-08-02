#ifndef CHECKBOXDELEGATE_HPP
#define CHECKBOXDELEGATE_HPP

#include <QStyledItemDelegate>


class CheckBoxDelegate : public QStyledItemDelegate
{
public:
    explicit CheckBoxDelegate(QObject* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


#endif // CHECKBOXDELEGATE_HPP
