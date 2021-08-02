#include <utility>
#include "ObjectModel.hpp"
#include "Objects/IObject.hpp"


ObjectModel::ObjectModel(std::shared_ptr<Scene> scene, QObject *parent)
    : QAbstractTableModel(parent), scene(std::move(scene))
{
}

int ObjectModel::rowCount(const QModelIndex &parent) const
{
    return std::distance(scene->begin(), scene->end());
}

int ObjectModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant ObjectModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    auto objectIter = scene->begin();
    std::advance(objectIter, index.row());

    QString name = QString::fromStdString((*objectIter)->getName());
    bool visible = true;
    bool selected = (*objectIter)->isSelected();

    QVariantList list;
    list.push_back(name);
    list.push_back(visible);
    list.push_back(selected);

    return list.value(index.column());
}
