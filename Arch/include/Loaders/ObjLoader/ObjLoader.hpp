#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include <vector>
#include "Loaders/ILoader.hpp"

namespace Core { class Vertex; class Vec; }


class ObjLoader : public ILoader
{
public:
    explicit ObjLoader(std::string  filename);

    virtual std::unique_ptr<IObject> loadObject() override;
    virtual std::unique_ptr<Scene> loadScene() override;

protected:
    static Core::Vertex extractVertex(const std::string& str,
                                      const std::vector<Core::Vec>& verts,
                                      const std::vector<Core::Vec>& norms,
                                      const std::vector<Core::Vec>& uvs);

private:
    std::string filename;
};

#endif // OBJLOADER_HPP
