//
// Created by rulldeef on 11/26/21.
//

#include <sstream>
#include "Scene/Scene.hpp"
#include "Importers/UdfImporter/UdfImporter.hpp"
#include "Builders/SceneBuidler.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/Adapters/MeshAdapter.hpp"
#include "Objects/Adapters/CameraAdapter.hpp"
#include "Objects/Adapters/LightAdapter.hpp"
#include "Builders/BaseMeshBuilder.hpp"


std::shared_ptr<Scene> UdfImporter::importScene(std::istream& stream)
{
    std::string line;
    std::getline(stream, line);

    if (line != "S")
        throw std::runtime_error("bad scene format: not \"S\"");

    SceneBuilder sceneBuilder;
    sceneBuilder.prepare();

    while (true)
    {
        auto pos = stream.tellg();
        std::getline(stream, line);

        if (line != "O")
            break;
        else
        {
            stream.seekg(pos, std::ios::beg);
            auto obj = importObject(stream);
            sceneBuilder.addObject(obj);
        }
    }

    if (line != "ES")
        throw std::runtime_error("bad scene format: not \"ES\"");

    return sceneBuilder.build();
}

static Vector readVector(const std::string &string, double w)
{
    double x, y, z;
    std::stringstream(string) >> x >> y >> z;
    return Vector(x, y, z, w);
}

std::shared_ptr<IObject> UdfImporter::importObject(std::istream &stream)
{
    std::string line;
    std::getline(stream, line);

    if (line != "O")
        throw std::runtime_error("bad object format: not \"O\"");

    std::getline(stream, line);
    auto id = std::strtoull(line.c_str(), NULL, 10);
    std::getline(stream, line);

    std::string name = line;
    std::getline(stream, line);

    std::shared_ptr<IObject> obj;

    if (line == "mesh")
    {
        auto mesh = importMesh(stream);
        obj = std::shared_ptr<IObject>(new ObjectAdapter<Mesh>(id, std::move(mesh)));
    }
    else if (line == "camera")
    {
        auto camera = importCamera(stream);
        obj = std::shared_ptr<IObject>(new ObjectAdapter<Camera>(id, camera));
    }
    else if (line == "light")
    {
        auto light = importLight(stream);
        obj = std::shared_ptr<IObject>(new ObjectAdapter<Light>(id, light));
    }
    else
        throw std::runtime_error("bad object format: no data");

    obj->setName(name);

    std::getline(stream, line);
    obj->setPosition(readVector(line, 1.0));
    std::getline(stream, line);
    obj->setRotation(readVector(line, 0.0));
    std::getline(stream, line);
    obj->setScale(readVector(line, 0.0));

    std::getline(stream, line);

    if (line != "EO")
        throw std::runtime_error("bad object format: not \"EO\"");

    return obj;
}

static std::vector<size_t> readFace(const std::string& string)
{
    size_t v1, v2, v3, n1, n2, n3;
    char tmp;
    std::stringstream(string) >> v1 >> tmp >> n1 >> v2 >> tmp >> n2 >> v3 >> tmp >> n3;
    return std::initializer_list<size_t> {v1, n1, v2, n2, v3, n3};
}

Mesh UdfImporter::importMesh(std::istream& stream)
{
    std::string line;
    std::getline(stream, line);

    if (line != "M")
        throw std::runtime_error("bad mesh format: not \"M\"");

    BaseMeshBuilder builder;

//    std::vector<Vector> vertices;
//    std::vector<Vector> normals;
//    std::vector<std::vector<size_t>> faces;

    while (line != "EM")
    {
        std::getline(stream, line);

        if (line == "v")
        {
            std::getline(stream, line);
            // vertices.push_back(readVector(line, 1.0));
            builder.pushPos(readVector(line, 1.0));
        }
        else if (line == "n")
        {
            std::getline(stream, line);
            // normals.push_back(readVector(line, 0.0));
            builder.pushNorm(readVector(line, 0.0));
        }
        else if (line == "f")
        {
            std::getline(stream, line);
            auto inds = readFace(line);
            // faces.push_back(readFace(line));
            builder.linkFace(inds[0], inds[2], inds[4], inds[1], inds[3], inds[5]);
        }
    }

//    Core::Mesh mesh = Core::make_mesh(faces.size());
//
//    for (const auto& faceIndices : faces)
//    {
//        Vector v1 = vertices[faceIndices[0]];
//        Vector v2 = vertices[faceIndices[2]];
//        Vector v3 = vertices[faceIndices[4]];
//
//        Vector n1 = normals[faceIndices[1]];
//        Vector n2 = normals[faceIndices[3]];
//        Vector n3 = normals[faceIndices[5]];
//
//        Core::Vertex vr1 = Core::make_vertex(v1, n1);
//        Core::Vertex vr2 = Core::make_vertex(v2, n2);
//        Core::Vertex vr3 = Core::make_vertex(v3, n3);
//
//        add_face(mesh, Core::make_face(vr1, vr2, vr3));
//    }

//    return Mesh(mesh);

    return builder.build();
}

Camera UdfImporter::importCamera(std::istream& stream)
{
    std::string line;

    std::getline(stream, line);
    if (line != "C")
        throw std::runtime_error("invalid camera format");

    std::getline(stream, line);
    double pitch = strtod(line.c_str(), nullptr);

    std::getline(stream, line);
    double yaw = strtod(line.c_str(), nullptr);

    std::getline(stream, line);
    if (line != "EC")
        throw std::runtime_error("invalid camera format");

    return Camera(Vector(), pitch, yaw);
}

Light UdfImporter::importLight(std::istream& stream)
{
    std::string line;
    Light light;

    std::getline(stream, line);
    if (line != "L")
        throw std::runtime_error("invalid light format"); ///TODO: add exception classes

    std::getline(stream, line);
    if (line == "ambient")
        light.setType(Light::Type::Ambient);
    else if (line == "directional")
        light.setType(Light::Type::Directional);
    ///TODO: add support for point light

    std::getline(stream, line);
    light.setColor(readVector(line, 1.0));

    std::getline(stream, line);
    double intensity = strtod(line.c_str(), nullptr);
    light.setIntensity(intensity);

    std::getline(stream, line);
    if (line != "EL")
        throw std::runtime_error("invalid light format");

    return light;
}
