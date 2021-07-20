#include <vector>
#include <fstream>
#include <algorithm>
#include "Mesh.hpp"
#include "ObjLoader.hpp"
#include "ObjectAdapter.hpp"


ObjLoader::ObjLoader(const std::string& filename)
    : filename(filename)
{
}

std::unique_ptr<IObject> ObjLoader::loadObject()
{
    // loads only meshes for now

    std::ifstream file(filename);
    std::string line, sym;

    std::vector<Core::Vec> verts;
    std::vector<Core::Vec> norms;

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

        }
    }

    return std::unique_ptr<IObject>(new ObjectAdapter<Mesh>(mesh));
}

static Core::Vertex ObjLoader::extractVertex(const std::string &str, const std::vector<Core::Vec>& verts, const std::vector<Core::Vec>& norms)
{
    Core::Vertex res;
    res.position = Core::make_pos(0, 0, 0);
    res.normal = Core::make_dir(0, 0, 0);
    res.uv = Core::make_pos(0, 0, 0);

    size_t slashes = std::count(str.begin(), str.end(), '/');
    if (slashes == 0)
        res.position = verts[std::stoi(str)];
    else if (slashes == 1)
    {
        res.position = verts[std::stoi(std::string(str.begin(), str.begin() + str.find('/')))];
        
    }

    return res;
}
