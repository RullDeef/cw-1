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
            std::vector<Core::Vertex> face_verts;
            std::string vert;
            ss.ignore(1);
            while (std::getline(ss, vert, ' '))
                face_verts.push_back(extractVertex(vert, verts, norms));

            size_t i1 = 0;
            size_t i2 = 1;
            size_t i3 = 2;

            while (i3 < face_verts.size())
            {
                Core::Face face = Core::make_face(face_verts[i1], face_verts[i2], face_verts[i3]);
                faces.push_back(face);
                i2++;
                i3++;
            }
        }
    }

    Core::Mesh mesh = Core::make_mesh(faces.size());
    for (const auto& face : faces)
        Core::add_face(mesh, face);

    size_t id = -1;
    auto object = std::unique_ptr<IObject>(new ObjectAdapter<Core::Mesh>(id, mesh, AdapterPolicy::StrongOwnership));
    object->setName(filename.substr(filename.rfind('/') + 1, filename.find('.') - filename.rfind('/') - 1));
    return object;
}

Core::Vertex ObjLoader::extractVertex(const std::string &str, const std::vector<Core::Vec>& verts, const std::vector<Core::Vec>& norms)
{
    Core::Vec position{};
    size_t slashes = std::count(str.begin(), str.end(), '/');

    if (slashes == 0)
    {
        position = verts[std::stoi(str) - 1];
    }
    else if (slashes == 1)
    {
        size_t pos = str.find('/');
        size_t index = std::stoi(std::string(str.begin(), str.begin() + str.find('/')));
        position = verts[index - 1];
    }
    else
    {
        size_t index = std::stoi(std::string(str.begin(), str.begin() + str.find('/')));
        position = verts[index - 1];
    }

    return Core::make_vertex(position);
}

std::unique_ptr<Scene> ObjLoader::loadScene() {
    return std::make_unique<Scene>();
}
