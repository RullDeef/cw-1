#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstring>
#include <Loaders/ObjLoader/ObjFace.hpp>
#include "Core/Objects/Mesh.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Loaders/ObjLoader/ObjLoader.hpp"


std::unique_ptr<Scene> ObjLoader::loadScene(const std::string &filename)
{
    return std::make_unique<Scene>();
}

std::unique_ptr<IObject> ObjLoader::loadMesh(const std::string& filename)
{
    /// TODO: load materials as well
    std::ifstream file(filename);

    auto verts = extractGeometry(file);
    auto uvs = extractTextureUV(file);
    auto norms = extractNormals(file);

    auto meshes = extractMeshesList(file);

    /// TODO: get rid of assumption (hint: use group object adapter)
    /// ASSUMPTION (!)
    /// mesh list size == 1

    size_t id = -1;
    Mesh mesh = constructMesh(meshes.front().second, verts, uvs, norms);

    auto object = std::unique_ptr<IObject>(new ObjectAdapter<Mesh>(id, std::move(mesh)));
    object->setName(meshes.front().first);
    return object;
}
std::unique_ptr<IObject> ObjLoader::loadCamera(const std::string &filename)
{
    return nullptr;
}

std::unique_ptr<IObject> ObjLoader::loadLight(const std::string &filename)
{
    return nullptr;
}

std::vector<Vector> ObjLoader::extractGeometry(std::ifstream &file)
{
    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::vector<Vector> result = { Vector() }; /// for index adjustment
    std::string line;
    while (std::getline(file, line))
    {
        line = trim(line);
        if (line.empty())
            continue;

        if (acceptWhenToken(line, "v"))
            result.push_back(extractVector3(line, 1.0));
    }

    return result;
}

std::vector<Vector> ObjLoader::extractTextureUV(std::ifstream &file)
{
    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::vector<Vector> result = { Vector() };
    std::string line;
    while (std::getline(file, line))
    {
        line = trim(line);
        if (line.empty())
            continue;

        if (acceptWhenToken(line, "vt"))
            result.push_back(extractVector2(line));
    }

    return result;
}

std::vector<Vector> ObjLoader::extractNormals(std::ifstream &file)
{
    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::vector<Vector> result = { Vector() };
    std::string line;
    while (std::getline(file, line))
    {
        line = trim(line);
        if (line.empty())
            continue;

        if (acceptWhenToken(line, "vn"))
            result.push_back(extractVector3(line, 0.0));
    }

    return result;
}

std::list<ObjLoader::ObjObject> ObjLoader::extractMeshesList(std::ifstream &file)
{
    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::list<ObjObject> result;
    std::vector<ObjFace> currFaces;
    std::string currName;

    std::string line;
    while (std::getline(file, line))
    {
        if (acceptWhenToken(line, "o"))
        {
            result.emplace_back(currName, currFaces);
            currName = line;
            currFaces.clear();
        }
        else if (acceptWhenToken(line, "f"))
        {
            auto triangles = ObjFace(line).triangulate();
            currFaces.insert(currFaces.end(), triangles.begin(), triangles.end());
        }
    }

    result.emplace_back(currName, currFaces);
    result.erase(result.begin());

    return result;
}

bool ObjLoader::acceptWhenToken(std::string &line, const char *token)
{
    size_t len = strlen(token);
    if (line.substr(0, len) == token)
    {
        line = trim(line.substr(len));
        return true;
    }
    return false;
}

std::string ObjLoader::trim(const std::string &str)
{
    constexpr auto whitespaces = " \n\r\t";
    size_t first_i = str.find_first_not_of(whitespaces);
    size_t last_i = str.find_last_not_of(whitespaces);

    return str.substr(first_i, last_i);
}

Vector ObjLoader::extractVector2(const std::string &str)
{
    std::istringstream ss(str);
    double x, y;

    ss >> x >> y;
    return Vector(x, y, 0.0, 0.0);
}

Vector ObjLoader::extractVector3(const std::string& str, double w)
{
    std::istringstream ss(str);
    double x, y, z;

    ss >> x >> y >> z;
    return Vector(x, y, z, w);
}

Mesh ObjLoader::constructMesh(const ObjLoader::ObjFaceList &faces, const std::vector<Vector> &positions,
                              const std::vector<Vector> &textures, const std::vector<Vector> &normals)
{
    Core::Mesh mesh = Core::make_mesh(faces.size());

    for (const auto& objFace : faces)
    {
        const auto& vList = objFace.getVertexList();

        Core::Vertex v1 = Core::make_vertex(positions[vList[0].getPosIndex()]);
        Core::Vertex v2 = Core::make_vertex(positions[vList[1].getPosIndex()]);
        Core::Vertex v3 = Core::make_vertex(positions[vList[2].getPosIndex()]);

        if (objFace.hasTexIndex())
        {
            v1.uv = textures[vList[0].getTexIndex()];
            v2.uv = textures[vList[1].getTexIndex()];
            v3.uv = textures[vList[2].getTexIndex()];
        }

        if (objFace.hasNormIndex())
        {
            v1.normal = normals[vList[0].getNormIndex()];
            v2.normal = normals[vList[1].getNormIndex()];
            v3.normal = normals[vList[2].getNormIndex()];
        }

        Core::Face face = Core::make_face(v1, v2, v3);
        Core::add_face(mesh, face);
    }

    return Mesh(mesh);
}
