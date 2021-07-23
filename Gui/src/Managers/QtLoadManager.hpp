#ifndef QTLOADMANAGER_HPP
#define QTLOADMANAGER_HPP

#include "LoadManager.hpp"


class QtLoadManager : public LoadManager
{
public:
    explicit QtLoadManager(IManagerFactory& factory, QWidget* dialogParent);

    virtual void loadMesh() override;

protected:
    std::string getFilename();

    QWidget* dialogParent;
};

#endif // QTLOADMANAGER_HPP
