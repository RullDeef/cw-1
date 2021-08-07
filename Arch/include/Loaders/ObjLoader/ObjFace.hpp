#ifndef OBJFACE_HPP
#define OBJFACE_HPP

#include <vector>
#include "Loaders/ObjLoader/ObjVertex.hpp"


class ObjFace
{
public:
    explicit ObjFace(const std::string& str);

    [[nodiscard]] bool hasTexIndex() const;
    [[nodiscard]] bool hasNormIndex() const;

    [[nodiscard]] inline const std::vector<ObjVertex>& getVertexList() const { return vertexList; }
    [[nodiscard]] std::vector<ObjFace> triangulate() const;

private:
    ObjFace(const ObjVertex& v1, const ObjVertex& v2, const ObjVertex& v3);

    [[nodiscard]] ObjFace getTriangle(size_t i, size_t j, size_t k) const;

    std::vector<ObjVertex> vertexList;
};

#endif // OBJFACE_HPP
