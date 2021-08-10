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

QVariant ObjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (section == 0)
            return "Object name";
        else if (section == 1)
            return "Visible";
        else if (section == 2)
            return "Selected";
        else
            return "";
    }

    return QVariant();
}

void ObjectModel::setScene(Scene& newScene)
{
    beginResetModel();
    scene = &newScene;
    endResetModel();

    emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
}

void ObjectModel::objectUpdated(std::shared_ptr<IObject> object)
{
    /// TODO: emit soft signal
    emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
}
