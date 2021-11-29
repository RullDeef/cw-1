//
// Created by rulldeef on 11/27/21.
//

#ifndef BASEMESHBUILDER_HPP
#define BASEMESHBUILDER_HPP

#include <vector>
#include "Math/Vector.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/Material.hpp"


class BaseMeshBuilder
{
    struct MBFace
    {
        size_t p1, p2, p3, n1, n2, n3;
        const static size_t npos = static_cast<size_t>(-1);
    };

public:
    virtual ~BaseMeshBuilder() = default;

    BaseMeshBuilder& pushPos(const Vector& pos);
    BaseMeshBuilder& pushNorm(const Vector& norm);

    BaseMeshBuilder& linkFace(size_t p1, size_t p2, size_t p3);
    BaseMeshBuilder& linkFace(size_t p1, size_t p2, size_t p3, size_t n);
    BaseMeshBuilder& linkFace(size_t p1, size_t p2, size_t p3, size_t n1, size_t n2, size_t n3);

    BaseMeshBuilder& useMaterial(const Material& mat);

    virtual Mesh build();

private:
    std::vector<Vector> vPoses;
    std::vector<Vector> vNorms;

    Material material;

    std::vector<MBFace> faces;
};

#endif //BASEMESHBUILDER_HPP
