#include <QFileDialog>
#include "QtPortManager.hpp"

QtPortManager::QtPortManager(IManagerFactory &factory) : PortManager(factory)
{
}

std::string QtPortManager::requestFilename()
{
    QString qfilename = QFileDialog::getOpenFileName(nullptr, "Select file", nullptr,
                                                     "", nullptr,
                                                     QFileDialog::DontUseNativeDialog);
    return qfilename.toStdString();
}

void QtPortManager::onSceneExport(const std::string &filename, std::shared_ptr<Scene> scene)
{
    PortManager::onSceneExport(filename, scene);
    emit sceneExportedSignal(scene);
}

void QtPortManager::onSceneImport(const std::string &filename, std::shared_ptr<Scene> scene)
{
    PortManager::onSceneImport(filename, scene);
    emit sceneImportedSignal(scene);
}

void QtPortManager::onObjectImport(const std::string &filename, std::shared_ptr<IObject> object)
{
    PortManager::onObjectImport(filename, object);
    emit objectImportedSignal(object);
}
