#ifndef OBJECTMODEL_HPP
#define OBJECTMODEL_HPP

#include <QAbstractItemModel>
#include <memory>
#include <Scene/Scene.hpp>
#include <Managers/IManagerFactory.hpp>


class ObjectModel : public QAbstractTableModel
{
public:
    explicit ObjectModel(IManagerFactory& managerFactory, QObject* parent = nullptr);
    virtual ~ObjectModel() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

protected slots:
    void triggerUpdateSlot();

private:
    Scene* requireActiveScene() const;

    IManagerFactory* managerFactory;
};

#endif // OBJECTMODEL_HPP
