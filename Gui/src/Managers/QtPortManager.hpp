#ifndef QTPORTMANAGER_HPP
#define QTPORTMANAGER_HPP

#include <QObject>
#include <Managers/PortManager.hpp>


class QtPortManager : public QObject, public PortManager
{
    Q_OBJECT

public:
    explicit QtPortManager(IManagerFactory& factory);

signals:
    void sceneImportedSignal(std::shared_ptr<Scene> scene);
    void sceneExportedSignal(std::shared_ptr<Scene> scene);
    void objectImportedSignal(std::shared_ptr<IObject> object);

protected:
    std::string requestFilename() override;

    void onSceneExport(const std::string &filename, std::shared_ptr<Scene> scene) override;
    void onSceneImport(const std::string &filename, std::shared_ptr<Scene> scene) override;
    void onObjectImport(const std::string &filename, std::shared_ptr<IObject> object) override;
};

#endif // QTPORTMANAGER_HPP
