//
// Created by rulldeef on 11/26/21.
//

#include "Exporters/UdfEXporter/UdfExporter.hpp"
#include <string>
#include "Scene/Scene.hpp"
#include "Objects/Adapters/MeshAdapter.hpp"


void UdfExporter::exportScene(std::ostream& stream, std::shared_ptr<Scene> scene)
{
    if (!scene)
        throw std::runtime_error("bad scene for export");

    stream << std::string("S\n");
    for (auto obj : *scene)
        exportObject(stream, obj);
    stream << std::string("ES\n");
}

static std::ostream& operator<<(std::ostream& stream, const Vector& v)
{
    return stream << v.getX() << " " << v.getY() << " " << v.getZ();
}

void UdfExporter::exportObject(std::ostream& stream, std::shared_ptr<IObject> object)
{
    stream << "O\n";
    stream << object->getId() << std::endl;
    stream << object->getName() << std::endl;

    if (auto adapter = dynamic_cast<ObjectAdapter<Mesh>*>(object.get()))
    {
        stream << "mesh\n";
        exportMesh(stream, adapter->getAdaptee());
    }
    else if (auto adapter = dynamic_cast<ObjectAdapter<Camera>*>(object.get()))
    {
        stream << "camera\n";
        exportCamera(stream, adapter->getAdaptee());
    }
    else if (auto adapter = dynamic_cast<ObjectAdapter<Light>*>(object.get()))
    {
        stream << "light\n";
        exportLight(stream, adapter->getAdaptee());
    }
    else
        throw std::runtime_error("unrecognized object type");

    stream << object->getPosition() << std::endl;
    stream << object->getRotation() << std::endl;
    stream << object->getScale() << std::endl;
    stream << "EO\n";
}

static void extractVerticesNormals(std::vector<Vector>& verts, std::vector<Vector>& norms, const Mesh& mesh)
{
    auto raw = (Core::Mesh)mesh;
    verts.clear();
    norms.clear();

    for (size_t i = 0; i < raw.faces.size; i++) {
        auto face = raw.faces.data[i];
        verts.emplace_back(face.verts[0].position);
        verts.emplace_back(face.verts[1].position);
        verts.emplace_back(face.verts[2].position);

        norms.emplace_back(face.verts[0].normal);
        norms.emplace_back(face.verts[1].normal);
        norms.emplace_back(face.verts[2].normal);
    }
}

void UdfExporter::exportMesh(std::ostream& stream, const Mesh& mesh)
{
    std::vector<Vector> verts, norms;
    extractVerticesNormals(verts, norms, mesh);

    stream << std::string("M\n");

    for (const auto& pos: verts)
        stream << "v\n" << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;

    for (const auto& n: norms)
        stream << "n\n" << n.getX() << " " << n.getY() << " " << n.getZ() << std::endl;

    for (size_t i = 0; i < ((Core::Mesh)mesh).faces.size; i++)
        stream << "f\n" << 3 * i << "/" << 3 * i << " " << (3*i + 1) << "/" << (3*i + 1) << " " << (3*i + 2) << "/" << (3*i + 2) << std::endl;

    exportMaterial(stream, mesh.getMaterial());
    stream << std::string("EM\n");
}

void UdfExporter::exportCamera(std::ostream &stream, const Camera& camera)
{
    stream << "C\n";
    stream << camera.getPitch() << std::endl;
    stream << camera.getYaw() << std::endl;

    ///TODO: export fov near far as well

    stream << "EC\n";
}

void UdfExporter::exportLight(std::ostream &stream, const Light& light)
{
    stream << "L\n";

    switch (light.getType())
    {
        case Core::LightType::Ambient:
            stream << "ambient\n";
            break;
        case Core::LightType::Directional:
            stream << "directional\n";
            break;
        case Core::LightType::Point:
            stream << "point\n";
            break;
    }

    stream << (Vector)light.getColor() << std::endl;
    stream << light.getIntensity() << std::endl;
    stream << light.getAttenuation() << std::endl;
    stream << light.getRadius() << std::endl;
    stream << "EL\n";
}

void UdfExporter::exportMaterial(std::ostream &stream, const Material &material)
{
    stream << "mat\n";

    stream << material.getAmbientColor() << std::endl;
    stream << material.getDiffuseColor() << std::endl;
    stream << material.getSpecularColor() << std::endl;

    stream << material.getSpecularHighlight() << std::endl;
    stream << material.getOpacity() << std::endl;
    stream << material.getReflection() << std::endl;
    stream << material.getRefraction() << std::endl;
    stream << material.getRefractiveIndex() << std::endl;
}
