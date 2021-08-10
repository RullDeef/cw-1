#ifndef OBJECTMODEL_HPP
#define OBJECTMODEL_HPP

#include <QAbstractItemModel>
#include <memory>
#include <Scene/Scene.hpp>


class ObjectModel : public QAbstractTableModel
{
public:
    explicit ObjectModel(QObject* parent = nullptr);
    explicit ObjectModel(Scene& scene, QObject* parent = nullptr);
    virtual ~ObjectModel() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void setScene(Scene& newScene);

    void objectUpdated(std::shared_ptr<IObject> object);

private:
    Scene* scene = nullptr;
};

#endif // OBJECTMODEL_HPP
