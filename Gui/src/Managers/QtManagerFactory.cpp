#include "QtManagerFactory.hpp"
#include "QtLoadManager.hpp"


QtManagerFactory::QtManagerFactory(QWidget *mainWindow)
    : mainWindow(mainWindow)
{
}

std::shared_ptr<LoadManager> QtManagerFactory::getLoadManager()
{
    if (!loadManager)
        loadManager = std::shared_ptr<LoadManager>(new QtLoadManager(*this, mainWindow));
    return loadManager;
}
