#include <QFileDialog>
#include <QString>
#include "Managers/QtLoadManager.hpp"


QtLoadManager::QtLoadManager(IManagerFactory &factory, QWidget *dialogParent)
        : LoadManager(factory), dialogParent(dialogParent) // TODO: remove dependancy from parent widget
{
}

void QtLoadManager::loadMesh()
{
    std::string filename = getFilename();
    if (!filename.empty())
        _loadMesh(filename);
}

std::string QtLoadManager::getFilename()
{
    QString qfilename = QFileDialog::getOpenFileName(nullptr, u8"Выберите файл", nullptr,
                                                     QFileDialog::tr("OBJ Files (*.obj)"), nullptr,
                                                     QFileDialog::DontUseNativeDialog);
    return qfilename.toStdString();
}
