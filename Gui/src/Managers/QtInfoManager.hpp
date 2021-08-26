#ifndef QTINFOMANAGER_HPP
#define QTINFOMANAGER_HPP

#include <Managers/InfoManager.hpp>


class QtInfoManager : public InfoManager
{
public:
    explicit QtInfoManager(IManagerFactory& factory);

protected:
    void logMessage(const char *message, Type type) override;
};

#endif // QTINFOMANAGER_HPP
