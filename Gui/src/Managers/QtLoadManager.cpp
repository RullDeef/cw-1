#include <QFileDialog>
#include <Loaders/ObjLoader/ObjLoader.hpp>
#include "Managers/QtLoadManager.hpp"


QtLoadManager::QtLoadManager(IManagerFactory &factory)
        : LoadManager(factory)
{
    setLoader(std::shared_ptr<ILoader>(new ObjLoader()));
}

std::string QtLoadManager::requestFilename()
{
    QString qfilename = QFileDialog::getOpenFileName(nullptr, u8"Выберите файл", nullptr,
                                                     QFileDialog::tr("OBJ Files (*.obj)"), nullptr,
                                                     QFileDialog::DontUseNativeDialog);
    return qfilename.toStdString();
}

void QtLoadManager::onSceneLoad(std::shared_ptr<Scene> scene)
{
    LoadManager::onSceneLoad(scene);

    emit sceneLoadSignal(scene);
}

void QtLoadManager::onObjectLoad(std::shared_ptr<IObject> object)
{
    LoadManager::onObjectLoad(object);

    emit objectLoadSignal(object);
}
