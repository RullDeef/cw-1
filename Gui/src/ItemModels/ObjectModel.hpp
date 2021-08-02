#ifndef OBJECTMODEL_HPP
#define OBJECTMODEL_HPP

#include <QAbstractItemModel>
#include <memory>
#include <Scene/Scene.hpp>


class ObjectModel : public QAbstractTableModel
{
public:
    explicit ObjectModel(std::shared_ptr<Scene> scene, QObject* parent = nullptr);
    virtual ~ObjectModel() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::shared_ptr<Scene> scene;
};

#endif // OBJECTMODEL_HPP
