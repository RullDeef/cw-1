#ifndef IMANAGER_HPP
#define IMANAGER_HPP

class IManagerFactory;


class IManager
{
public:
    explicit IManager(IManagerFactory& factory);
    virtual ~IManager() = default;

protected:
    IManagerFactory& getFactory();

private:
    IManagerFactory* factory;
};

#endif // IMANAGER_HPP
