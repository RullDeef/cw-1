#include "Managers/InfoManager.hpp"


InfoManager::InfoManager(IManagerFactory &factory) : IManager(factory)
{
}

void InfoManager::logInfo(const char *message)
{
    logMessage(message, Type::INFO_MSG);
}

void InfoManager::logError(const char *message)
{
    logMessage(message, Type::ERROR_MSG);
}
