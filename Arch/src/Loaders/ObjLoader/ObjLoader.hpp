#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

#include <string>
#include "ILoader.hpp"

namespace Core { class Vertex; }


class ObjLoader : public ILoader
{
public:
    explicit ObjLoader(const std::string& filename);

    virtual std::unique_ptr<IObject> loadObject() override;
    virtual std::unique_ptr<Scene> loadScene() override;

protected:
    static Core::Vertex extractVertex(const std::string& str, const std::vector<Core::Vec>& verts, const std::vector<Core::Vec>& norms);

private:
    std::string filename;
};

#endif // OBJLOADER_HPP
