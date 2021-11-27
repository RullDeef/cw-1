//
// Created by rulldeef on 11/26/21.
//

#ifndef PORTMANAGER_HPP
#define PORTMANAGER_HPP

// port manager is used to import/export objects from/into surrounding world.
// replacement for load manager

#include "Managers/IManager.hpp"
#include <memory>

class IObject;
class Scene;


class PortManager : public IManager
{
public:
    explicit PortManager(IManagerFactory& factory);
    virtual ~PortManager() = default;

    void importScene(); // imports scene and makes it active
    void importMesh();
    void importCamera();
    void importLight();

    void exportScene(); // exports active scene

protected:
    virtual std::string requestFilename() = 0;

    virtual void beforeSceneImport(const std::string& filename, std::shared_ptr<Scene> scene);
    virtual void onSceneImport(const std::string& filename, std::shared_ptr<Scene> scene);

    virtual void beforeObjectImport(const std::string& filename, std::shared_ptr<IObject> object);
    virtual void onObjectImport(const std::string& filename, std::shared_ptr<IObject> object);

    virtual void beforeSceneExport(const std::string& filename, std::shared_ptr<Scene> scene);
    virtual void onSceneExport(const std::string& filename, std::shared_ptr<Scene> scene);
};

#endif //PORTMANAGER_HPP
