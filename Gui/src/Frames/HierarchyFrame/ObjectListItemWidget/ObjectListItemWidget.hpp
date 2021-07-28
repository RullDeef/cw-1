#ifndef OBJECTLISTITEMWIDGET_HPP
#define OBJECTLISTITEMWIDGET_HPP

#include <memory>
#include <QWidget>
#include <QLabel>
#include "Objects/IObject.hpp"


class ObjectListItemWidget : public QWidget
{
    Q_OBJECT

public:
    ObjectListItemWidget();
    virtual ~ObjectListItemWidget() = default;

    void setObject(std::weak_ptr<IObject> newObject);

    bool isValid() const;

protected:
    void updateView();

private:
    std::weak_ptr<IObject> object;

    QLabel* idLabel;
    QLabel* nameLabel;
};

#endif // OBJECTLISTITEMWIDGET_HPP
