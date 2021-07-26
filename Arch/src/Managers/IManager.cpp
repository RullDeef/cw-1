#include "Managers/IManager.hpp"


IManager::IManager(IManagerFactory &factory)
        : factory(&factory)
{
}

IManagerFactory &IManager::getFactory()
{
    return *factory;
}
