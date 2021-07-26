#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include "Core/Objects/Mesh.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Loaders/ObjLoader/ObjLoader.hpp"


ObjLoader::ObjLoader(std::string filename)
    : filename(std::move(filename))
{
}

std::unique_ptr<IObject> ObjLoader::loadObject()
{
    // loads only meshes for now

    std::ifstream file(filename);
    std::string line, sym;

    std::vector<Core::Vec> verts;
    std::vector<Core::Vec> norms;
    std::vector<Core::Face> faces;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        if (!(ss >> sym)) continue;

        if (sym == "#") continue;
        else if (sym == "v")
        {
            double x, y, z;
            ss >> x >> y >> z;
            verts.push_back(Core::make_pos(x, y, z));
        }
        else if (sym == "vn")
        {
            double x, y, z;
            ss >> x >> y >> z;
            norms.push_back(Core::make_dir(x, y, z));
        }
        else if (sym == "f")
        {
            std::string s1, s2, s3;
            ss >> s1 >> s2 >> s3;

            Core::Face face{};
            face.verts[0] = extractVertex(s1, verts, norms);
            face.verts[1] = extractVertex(s2, verts, norms);
            face.verts[2] = extractVertex(s3, verts, norms);
            faces.push_back(face);
        }
    }

    Core::Mesh mesh{};

    mesh.faces = Core::make_vect<Core::Face>(faces.size());
    mesh.faces.size = faces.size();
    size_t i = 0;
    for (const auto& face : faces)
        Core::set(mesh.faces, i++, face);

    size_t id = -1;
    return std::unique_ptr<IObject>(new ObjectAdapter<Core::Mesh>(id, mesh, AdapterPolicy::StrongOwnership));
}

Core::Vertex ObjLoader::extractVertex(const std::string &str, const std::vector<Core::Vec>& verts, const std::vector<Core::Vec>& norms)
{
    Core::Vertex res{};
    res.position = Core::make_pos(0, 0, 0);
    res.normal = Core::make_dir(0, 0, 0);
    res.uv = Core::make_pos(0, 0, 0);

    size_t slashes = std::count(str.begin(), str.end(), '/');

    if (slashes == 0)
    {
        res.position = verts[std::stoi(str) - 1];
    }
    else if (slashes == 1)
    {
        size_t pos = str.find('/');
        size_t index = std::stoi(std::string(str.begin(), str.begin() + str.find('/')));
        res.position = verts[index - 1];
    }
    else
    {
        size_t index = std::stoi(std::string(str.begin(), str.begin() + str.find('/')));
        res.position = verts[index - 1];
    }

    return res;
}

std::unique_ptr<Scene> ObjLoader::loadScene() {
    return std::make_unique<Scene>();
}
