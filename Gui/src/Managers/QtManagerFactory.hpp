#ifndef QTMANAGERFACTORY_HPP
#define QTMANAGERFACTORY_HPP

#include <QWidget>
#include "IManagerFactory.hpp"

class QtManagerFactory : public IManagerFactory
{
public:
    explicit QtManagerFactory(QWidget* mainWindow);
    std::shared_ptr<LoadManager> getLoadManager() override;

private:
    std::shared_ptr<LoadManager> loadManager;
    QWidget* mainWindow;
};

#endif // QTMANAGERFACTORY_HPP
