#include <utility>
#include <QLayout>
#include "ObjectListItemWidget.hpp"


ObjectListItemWidget::ObjectListItemWidget()
{
    setLayout(new QHBoxLayout());
    idLabel = new QLabel();
    nameLabel = new QLabel();

    layout()->addWidget(idLabel);
    layout()->addWidget(nameLabel);
}

void ObjectListItemWidget::setObject(std::weak_ptr<IObject> newObject)
{
    object = std::move(newObject);
    updateView();
}

bool ObjectListItemWidget::isValid() const
{
    return not object.expired();
}

void ObjectListItemWidget::updateView()
{
    if (auto obj = object.lock())
    {
        idLabel->setText(QString::number(obj->getId()));
        nameLabel->setText(QString::fromStdString(obj->getName()));
    }
    else
    {
        idLabel->setText("X");
        nameLabel->setText("(...)");
    }
}
