#include <utility>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include <cstring>
#include <Builders/BaseMeshBuilder.hpp>
#include "Objects/Mesh.hpp"
#include "Objects/ObjectAdapter.hpp"
#include "Scene/Scene.hpp"
#include "Builders/DefaultIDGenerator.hpp"
#include "Loaders/ObjLoader/ObjFace.hpp"
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

    auto mtllibnames = extractMatLibs(file, filename);
    auto mtllibs = loadMaterials(mtllibnames);

    auto meshes = extractMeshesList(file);

    /// TODO: get rid of assumption (hint: use group object adapter)
    /// ASSUMPTION (!)
    /// mesh list size == 1


    if (meshes.size() == 0)
        throw std::runtime_error("bad meshes list");

    size_t id = DefaultIDGenerator().generate();
    Mesh mesh = constructMesh(meshes.front(), verts, uvs, norms, mtllibs);

    auto object = std::unique_ptr<IObject>(new ObjectAdapter<Mesh>(id, std::move(mesh)));
    object->setName(meshes.front().getName());
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

    std::vector<Vector> result = { Vector(0, 0, 0, 1) }; /// for index adjustment
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

    std::vector<Vector> result = { Vector(0, 0, 0, 0) };
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

    std::vector<Vector> result = { Vector(0, 0, 0, 0) };
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

std::vector<std::string> ObjLoader::extractMatLibs(std::ifstream& file, std::string baseFilename)
{
    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::vector<std::string> result;
    baseFilename = baseFilename.substr(0, 1 + baseFilename.find_last_of("/\\"));

    std::string line;
    while (std::getline(file, line))
        if (acceptWhenToken(line, "mtllib"))
            result.push_back(baseFilename + line);

    return result;
}

std::list<ObjObject> ObjLoader::extractMeshesList(std::ifstream &file)
{
    file.clear();
    file.seekg(0, std::ios_base::beg);

    std::list<ObjObject> result;
    ObjObject currObject;

    std::string line;
    while (std::getline(file, line))
    {
        if (acceptWhenToken(line, "o"))
        {
            result.push_back(currObject);
            currObject = ObjObject(line);
        }
        else if (acceptWhenToken(line, "usemtl"))
            currObject.setMaterialName(line);
        else if (acceptWhenToken(line, "f"))
            for (const auto& face : ObjFace(line).triangulate())
                currObject.addFace(face);
    }

    result.push_back(currObject);
    if (result.front().empty())
        result.erase(result.begin());

    return result;
}

std::map<std::string, Material> ObjLoader::loadMaterials(const std::vector<std::string>& filenames)
{
    std::map<std::string, Material> result;

    for (const auto& filename : filenames)
        result.merge(loadMaterials(filename));

    return result;
}

std::map<std::string, Material> ObjLoader::loadMaterials(const std::string& filename)
{
    std::map<std::string, Material> result;

    std::ifstream file(filename);
    std::string line;

    std::string currName;
    Material currMat;
    while (std::getline(file, line))
    {
        if (acceptWhenToken(line, "newmtl"))
        {
            if (!currName.empty())
                result[currName] = currMat;

            currName = line;
            currMat = Material();
        }
        else if (acceptWhenToken(line, "Ka"))
        {
            auto color = extractVector3(line, 1.0);
            currMat.setAmbientColor(color);
        }
        else if (acceptWhenToken(line, "Kd"))
        {
            auto color = extractVector3(line, 1.0);
            currMat.setDiffuseColor(color);
        }
        else if (acceptWhenToken(line, "Ks"))
        {
            auto color = extractVector3(line, 1.0);
            currMat.setSpecularColor(color);
        }
        else if (acceptWhenToken(line, "Ns"))
        {
            double value = extractScalar(line);
            currMat.setSpecularHighlight(value);
        }
        else if (acceptWhenToken(line, "d"))
        {
            double value = extractScalar(line);
            currMat.setOpacity(value);
        }
    }

    if (!currName.empty())
        result[currName] = currMat;

    return result;
}

bool ObjLoader::acceptWhenToken(std::string &line, const char *token)
{
    size_t len = strlen(token);
    if (line.substr(0, len) == token)
    {
        line = trim(line.substr(len));
        return !line.empty();
    }
    return false;
}

std::string ObjLoader::trim(const std::string &str)
{
    constexpr auto whitespaces = " \n\r\t";
    size_t first_i = str.find_first_not_of(whitespaces);
    size_t last_i = str.find_last_not_of(whitespaces);

    if (first_i == std::string::npos)
        return "";
    else
        return str.substr(first_i, last_i);
}

double ObjLoader::extractScalar(const std::string &str)
{
    double value;
    std::stringstream(str) >> value;
    return value;
}

Vector ObjLoader::extractVector2(const std::string &str)
{
    double x, y;
    std::istringstream(str) >> x >> y;
    return Vector(x, y, 0.0, 0.0);
}

Vector ObjLoader::extractVector3(const std::string& str, double w)
{
    std::istringstream ss(str);
    double x, y, z;

    ss >> x >> y >> z;
    return Vector(x, y, z, w);
}

Mesh ObjLoader::constructMesh(const ObjObject &object, const std::vector<Vector> &positions,
                                  const std::vector<Vector> &textures, const std::vector<Vector> &normals,
                                  const std::map<std::string, Material>& materialLib)
{
    BaseMeshBuilder builder;

    for (auto& pos : positions)
        builder.pushPos(pos);
    for (auto& norm : normals)
        builder.pushNorm(norm);

    for (const auto& face : object)
    {
        const auto& verts = face.getVertexList();
        if (verts.size() < 3)
            throw std::runtime_error("bad verts count for face");

        // make triangle fan
        auto v1 = verts[0];
        for (size_t i = 2; i < verts.size(); i++)
        {
            auto v2 = verts[i - 1], v3 = verts[i];

            if (v1.hasNormIndex() && v2.hasNormIndex() && v3.hasNormIndex())
                builder.linkFace(v1.getPosIndex(), v2.getPosIndex(), v3.getPosIndex(),
                                 v1.getNormIndex(), v2.getNormIndex(), v3.getNormIndex());
            else
                builder.linkFace(v1.getPosIndex(), v2.getPosIndex(), v3.getPosIndex());
        }
    }

    return builder.buildMesh();
}

Mesh constructMesh_old(const ObjObject &object, const std::vector<Vector> &positions,
                              const std::vector<Vector> &textures, const std::vector<Vector> &normals,
                              const std::map<std::string, Material>& materialLib)
{
    Core::Mesh mesh = Core::make_mesh(object.end() - object.begin());

    for (const auto& objFace : object)
    {
        auto vList = objFace.getVertexList();

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
        if (!objFace.hasNormIndex())
            Core::recalc_normal(face);
        Core::add_face(mesh, face);
    }

    Mesh result(mesh);

    if (!object.getMaterialName().empty())
        result.setMaterial(materialLib.at(object.getMaterialName()));

    return result;
}
