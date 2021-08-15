#include <utility>
#include "ObjectModel.hpp"
#include "Objects/IObject.hpp"
#include <Managers/SceneManager.hpp>
#include <Managers/QtSceneManager.hpp>
#include <Managers/QtSelectionManager.hpp>


ObjectModel::ObjectModel(IManagerFactory& managerFactory, QObject *parent)
    : QAbstractTableModel(parent), managerFactory(&managerFactory)
{
    auto sceneManager = dynamic_cast<QtSceneManager*>(managerFactory.getSceneManager().get());
    auto selectionManager = dynamic_cast<QtSelectionManager*>(managerFactory.getSelectionManager().get());

    connect(sceneManager, &QtSceneManager::activeSceneChangeSignal, this, &ObjectModel::triggerUpdateSlot);
    connect(sceneManager, &QtSceneManager::addObjectSignal, this, &ObjectModel::triggerUpdateSlot);
    connect(selectionManager, &QtSelectionManager::selectionChangedSignal, this, &ObjectModel::triggerUpdateSlot);
}

int ObjectModel::rowCount(const QModelIndex &parent) const
{
    Scene* scene = requireActiveScene();
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
    Scene* scene = requireActiveScene();
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

bool ObjectModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::EditRole && index.column() == 0)
    {
        Scene *scene = requireActiveScene();
        if (scene)
        {
            auto iter = scene->begin();
            std::advance(iter, index.row());
            managerFactory->getSelectionManager()->select(*iter);
        }
    }

    return true;
}

void ObjectModel::triggerUpdateSlot()
{
    beginResetModel();
    endResetModel();

    emit dataChanged(index(0, 0), index(rowCount(), columnCount()));
}

Scene *ObjectModel::requireActiveScene() const
{
    try
    {
        return &managerFactory->getSceneManager()->getActiveScene();
    }
    catch (...)
    {
        return nullptr;
    }
}
