#ifndef ILOADER_HPP
#define ILOADER_HPP

#include <memory>

class IObject;
class Scene;


class ILoader
{
public:
    virtual ~ILoader() = default;

    virtual std::unique_ptr<Scene> loadScene(const std::string& filename) = 0;

    virtual std::unique_ptr<IObject> loadMesh(const std::string& filename) = 0;
    virtual std::unique_ptr<IObject> loadCamera(const std::string& filename) = 0;
    virtual std::unique_ptr<IObject> loadLight(const std::string& filename) = 0;
};

#endif // ILOADER_HPP
