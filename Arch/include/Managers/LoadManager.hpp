#ifndef LOADMANAGER_HPP
#define LOADMANAGER_HPP

#include "SceneManager.hpp"
#include "IManager.hpp"


class LoadManager : public IManager
{
public:
    explicit LoadManager(IManagerFactory& factory);

    virtual void loadMesh() = 0;

protected:
    virtual void _loadMesh(const std::string& filename);
};


#endif // LOADMANAGER_HPP
