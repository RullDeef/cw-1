#ifndef ILOADER_HPP
#define ILOADER_HPP

#include <memory>

class IObject;
class Scene;


class ILoader
{
public:
    virtual ~ILoader() = default;

    virtual std::unique_ptr<IObject> loadObject() = 0;
    virtual std::unique_ptr<Scene> loadScene() = 0;
};

#endif // ILOADER_HPP
