#ifndef QTSCENEMANAGER_HPP
#define QTSCENEMANAGER_HPP

#include <QObject>
#include <Managers/SceneManager.hpp>


class QtSceneManager : public QObject, public SceneManager
{
    Q_OBJECT

public:
    explicit QtSceneManager(IManagerFactory& factory);

signals:
    void addSceneSignal(std::shared_ptr<Scene> scene);
    void activeSceneChangeSignal(std::shared_ptr<Scene> scene);
    void addObjectSignal(std::shared_ptr<IObject> object);

protected:
    void onAddScene(std::shared_ptr<Scene> scene) override;
    void onActiveSceneChange(std::shared_ptr<Scene> scene) override;
    void onAddObject(std::shared_ptr<IObject> object) override;
};

#endif // QTSCENEMANAGER_HPP
