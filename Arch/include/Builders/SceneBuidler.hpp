#ifndef SCENEBUIDLER_HPP
#define SCENEBUIDLER_HPP

#include <memory>

class IObject;
class Scene;


class SceneBuilder
{
public:
    SceneBuilder& prepare();
    SceneBuilder& addObject(std::shared_ptr<IObject> object);
    std::unique_ptr<Scene> build();

private:
    std::unique_ptr<Scene> scene;
};

#endif // SCENEBUIDLER_HPP
