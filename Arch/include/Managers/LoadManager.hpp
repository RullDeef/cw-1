#ifndef LOADMANAGER_HPP
#define LOADMANAGER_HPP

#include "IManager.hpp"
#include "Loaders/ILoader.hpp"
#include "Scene/Scene.hpp"


class LoadManager : public IManager
{
public:
    explicit LoadManager(IManagerFactory& factory);

    void loadEmptyScene();

    void loadScene();

    void loadMesh();
    void loadCamera();
    void loadLight();

    void buildCamera();
    void buildLight();

protected:
    void setLoader(std::shared_ptr<ILoader> newLoader);

    virtual std::string requestFilename() = 0;

    virtual void onSceneLoad(std::shared_ptr<Scene> scene);
    virtual void onObjectLoad(std::shared_ptr<IObject> object);

private:
    std::shared_ptr<ILoader> loader;
};

#endif // LOADMANAGER_HPP
