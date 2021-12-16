//
// Created by rulldeef on 11/26/21.
//

#ifndef UDFEXPORTER_HPP
#define UDFEXPORTER_HPP

// UDF - Universal data format

#include "Exporters/IExporter.hpp"

class Mesh;
class Camera;
class Light;
class Material;

class UdfExporter : public IExporter
{
public:
    virtual void exportScene(std::ostream& stream, std::shared_ptr<Scene> scene) override;

protected:
    void exportObject(std::ostream& stream, std::shared_ptr<IObject> object);
    static void exportMesh(std::ostream& stream, const Mesh& mesh);
    static void exportCamera(std::ostream& stream, const Camera& camera);
    static void exportLight(std::ostream& stream, const Light& light);
    static void exportMaterial(std::ostream& stream, const Material& material);
};

#endif //UDFEXPORTER_HPP
