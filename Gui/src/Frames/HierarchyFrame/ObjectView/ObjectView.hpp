#ifndef OBJECTVIEW_HPP
#define OBJECTVIEW_HPP

#include <QTableView>


class ObjectView : public QTableView
{
public:
    explicit ObjectView(QWidget* parent = nullptr);

protected:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;
    void doItemsLayout() override;

private:
    QItemSelection tempSelection;
};


#endif // OBJECTVIEW_HPP
