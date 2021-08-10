#ifndef OBJECTVIEW_HPP
#define OBJECTVIEW_HPP

#include <QTableView>


class ObjectView : public QTableView
{
public:
    explicit ObjectView(QWidget* parent = nullptr);

protected:
    void doItemsLayout() override;
};


#endif // OBJECTVIEW_HPP
