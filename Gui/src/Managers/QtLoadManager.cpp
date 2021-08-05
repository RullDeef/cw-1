#include <QFileDialog>
#include "Managers/QtLoadManager.hpp"


QtLoadManager::QtLoadManager(IManagerFactory &factory)
        : LoadManager(factory)
{
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
    emit sceneLoadSignal(scene);
}

void QtLoadManager::onObjectLoad(std::shared_ptr<IObject> object)
{
    emit objectLoadSignal(object);
}
