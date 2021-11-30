//
// Created by rulldeef on 11/27/21.
//

#ifndef BASEMESHBUILDER_HPP
#define BASEMESHBUILDER_HPP

#include <memory>
#include <vector>
#include "Math/Vector.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/Material.hpp"
#include "Builders/IObjectBuilder.hpp"

class IObject;


class BaseMeshBuilder : public IObjectBuilder
{
    struct MBFace
    {
        size_t p1, p2, p3, n1, n2, n3;
        const static size_t npos = static_cast<size_t>(-1);
    };

public:
    BaseMeshBuilder& pushPos(const Vector& pos);
    BaseMeshBuilder& pushNorm(const Vector& norm);

    BaseMeshBuilder& linkFace(size_t p1, size_t p2, size_t p3);
    BaseMeshBuilder& linkFace(size_t p1, size_t p2, size_t p3, size_t n);
    BaseMeshBuilder& linkFace(size_t p1, size_t p2, size_t p3, size_t n1, size_t n2, size_t n3);

    BaseMeshBuilder& useMaterial(const Material& mat);

    BaseMeshBuilder& setId(size_t newId);
    BaseMeshBuilder& setName(std::string newName);
    BaseMeshBuilder& setPosition(const Vector& newPosition);
    BaseMeshBuilder& setRotation(const Vector& newRotation);
    BaseMeshBuilder& setScale(const Vector& newScale);

    std::unique_ptr<IObject> build() override;

    virtual Mesh buildMesh();

private:
    Vector getPosAt(size_t index) const;
    Vector getNormAt(size_t index) const;

private:
    std::vector<Vector> vPoses;
    std::vector<Vector> vNorms;
    std::vector<MBFace> faces;
    Material material;

    size_t id;
    std::string name;
    Vector position = Vector(0, 0, 0, 1);
    Vector rotation = Vector(0, 0, 0, 0);
    Vector scale = Vector(1, 1, 1, 0);
};

#endif //BASEMESHBUILDER_HPP
