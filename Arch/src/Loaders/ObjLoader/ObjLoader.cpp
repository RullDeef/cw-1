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
    // loads only meshes for now /// TODO: load materials as well

    std::ifstream file(filename);
    std::string line, sym;

    /// TODO: refactor

    std::vector<Core::Vec> verts;
    std::vector<Core::Vec> norms;
    std::vector<Core::Vec> uvs;
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
        else if (sym == "vt")
        {
            double u, v, w = 0.0;
            ss >> u >> v >> w;
            uvs.push_back(Core::make_dir(u, v, w));
        }
        else if (sym == "vn")
        {
            double x, y, z;
            ss >> x >> y >> z; /// TODO: overload istream& operator>>(istream&, Vector&)
            norms.push_back(Core::normalised(Core::make_dir(x, y, z)));
        }
        else if (sym == "f")
        {
            std::vector<Core::Vertex> face_verts;
            std::string vert;
            ss.ignore(1);
            while (std::getline(ss, vert, ' '))
                face_verts.push_back(extractVertex(vert, verts, norms, uvs));

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
    /// TODO: refactor naming
    object->setName(filename.substr(filename.rfind('/') + 1, filename.find('.') - filename.rfind('/') - 1));
    return object;
}

Core::Vertex ObjLoader::extractVertex(const std::string &str, const std::vector<Core::Vec>& verts, const std::vector<Core::Vec>& norms, const std::vector<Core::Vec>& uvs)
{
    size_t slashes = std::count(str.begin(), str.end(), '/');

    if (slashes == 0)
    {
        size_t pos_index = std::stoi(str);
        Core::Vec position = verts[pos_index - 1];
        return Core::make_vertex(position);
    }
    else if (slashes == 1)
    {
        size_t slash_pos = str.find('/');
        size_t pos_index = std::stoi(str.substr(0, slash_pos));
        size_t uv_index = std::stoi(str.substr(slash_pos + 1));

        Core::Vec position = verts[pos_index - 1];
        Core::Vec uv = uvs[uv_index - 1];
        return Core::make_vertex(position, Core::make_dir(), uv);
    }
    else
    {
        size_t slash1_pos = str.find('/');
        size_t slash2_pos = str.rfind('/');

        size_t pos_index = std::stoi(str.substr(0, slash1_pos));
        size_t norm_index = std::stoi(str.substr(slash2_pos + 1));

        Core::Vec position = verts[pos_index - 1];
        Core::Vec normal = norms[norm_index - 1];

        // no uv coords
        if (slash1_pos + 1 == slash2_pos)
            return Core::make_vertex(position, normal);
        else
        {
            size_t uv_index = std::stoi(str.substr(slash1_pos + 1, slash2_pos - slash1_pos - 1));
            Core::Vec uv = uvs[uv_index - 1];
            return Core::make_vertex(position, normal, uv);
        }
    }
}

std::unique_ptr<Scene> ObjLoader::loadScene() {
    return std::make_unique<Scene>();
}
