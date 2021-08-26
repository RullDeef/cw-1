#ifndef INFOMANAGER_HPP
#define INFOMANAGER_HPP

#include "Managers/IManager.hpp"


class InfoManager : public IManager
{
public:
    enum class Type { INFO_MSG, ERROR_MSG };

    explicit InfoManager(IManagerFactory& factory);
    virtual ~InfoManager() = default;

    void logInfo(const char* message);
    void logError(const char* message);

protected:
    virtual void logMessage(const char* message, Type type) = 0;
};

#endif // INFOMANAGER_HPP
