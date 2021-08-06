#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <vector>
#include "Loaders/ILoader.hpp"

namespace Core { class Vertex; class Vec; }


class ObjLoader : public ILoader
{
public:
    virtual std::unique_ptr<Scene> loadScene(const std::string& filename) override;

    virtual std::unique_ptr<IObject> loadMesh(const std::string& filename) override;
    virtual std::unique_ptr<IObject> loadCamera(const std::string& filename) override;
    virtual std::unique_ptr<IObject> loadLight(const std::string& filename) override;

protected:
    static Core::Vertex extractVertex(const std::string& str,
                                      const std::vector<Core::Vec>& verts,
                                      const std::vector<Core::Vec>& norms,
                                      const std::vector<Core::Vec>& uvs);

    /// TODO: static std::map<std::string, Core::Material> loadMaterials(const std::string& filename);
};

#endif // OBJLOADER_HPP
