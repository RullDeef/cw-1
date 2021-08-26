#include <QApplication>
#include "QtInfoManager.hpp"
#include <QMainWindow>
#include <QStatusBar>


QtInfoManager::QtInfoManager(IManagerFactory &factory) : InfoManager(factory)
{
}

void QtInfoManager::logMessage(const char *message, InfoManager::Type type)
{
    QMainWindow *window = (QMainWindow*)QApplication::activeWindow();
    QStatusBar *statusBar = window->statusBar();

    statusBar->showMessage(message);
}
