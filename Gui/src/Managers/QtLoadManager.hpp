#ifndef QTLOADMANAGER_HPP
#define QTLOADMANAGER_HPP

#include <QObject>
#include <Managers/LoadManager.hpp>


class QtLoadManager : public QObject, public LoadManager
{
    Q_OBJECT

public:
    explicit QtLoadManager(IManagerFactory& factory);

signals:
    void sceneLoadSignal(std::shared_ptr<Scene> scene);
    void objectLoadSignal(std::shared_ptr<IObject> object);

protected:
    std::string requestFilename() override;

    void onSceneLoad(std::shared_ptr<Scene> scene) override;
    void onObjectLoad(std::shared_ptr<IObject> object) override;
};

#endif // QTLOADMANAGER_HPP
