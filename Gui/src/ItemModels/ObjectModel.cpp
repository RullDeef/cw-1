#include <utility>
#include "ObjectModel.hpp"
#include "Objects/IObject.hpp"


ObjectModel::ObjectModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

ObjectModel::ObjectModel(Scene& scene, QObject *parent)
    : QAbstractTableModel(parent), scene(&scene)
{
}

void ObjectModel::setScene(Scene& newScene)
{
    beginResetModel();
    scene = &newScene;
    endResetModel();

    emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
}

int ObjectModel::rowCount(const QModelIndex &parent) const
{
    if (!scene)
        return 0;

    return std::distance(scene->begin(), scene->end());
}

int ObjectModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant ObjectModel::data(const QModelIndex &index, int role) const
{
    if (!scene || !index.isValid() || role != Qt::DisplayRole)
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
