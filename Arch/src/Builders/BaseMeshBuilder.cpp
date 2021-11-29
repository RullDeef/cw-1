//
// Created by rulldeef on 11/27/21.
//

#include "Builders/BaseMeshBuilder.hpp"


BaseMeshBuilder &BaseMeshBuilder::pushPos(const Vector &pos)
{
    if (pos.getW() != 1.0)
        throw std::runtime_error("bad position");

    vPoses.push_back(pos);
    return *this;
}

BaseMeshBuilder &BaseMeshBuilder::pushNorm(const Vector &norm)
{
    if (norm.getW() != 0.0)
        throw std::runtime_error("bad normal");

    vNorms.push_back(norm);
    return *this;
}

BaseMeshBuilder &BaseMeshBuilder::linkFace(size_t p1, size_t p2, size_t p3)
{
    faces.push_back({p1, p2, p3, MBFace::npos, MBFace::npos, MBFace::npos});
    return *this;
}

BaseMeshBuilder &BaseMeshBuilder::linkFace(size_t p1, size_t p2, size_t p3, size_t n)
{
    faces.push_back({p1, p2, p3, n, n, n});
    return *this;
}

BaseMeshBuilder &BaseMeshBuilder::linkFace(size_t p1, size_t p2, size_t p3, size_t n1, size_t n2, size_t n3)
{
    faces.push_back({p1, p2, p3, n1, n2, n3});
    return *this;
}

BaseMeshBuilder &BaseMeshBuilder::useMaterial(const Material& mat)
{
    material = mat;
    return *this;
}

Mesh BaseMeshBuilder::build()
{
    auto mesh = Core::make_mesh(faces.size());

    for (auto face: faces)
    {
        Vector p1 = vPoses[face.p1];
        Vector p2 = vPoses[face.p2];
        Vector p3 = vPoses[face.p3];

        Vector n1(0, 0, 0, 0);
        Vector n2(0, 0, 0, 0);
        Vector n3(0, 0, 0, 0);
        if (face.n1 != MBFace::npos)
        {
            n1 = vNorms[face.n1];
            n2 = vNorms[face.n2];
            n3 = vNorms[face.n3];
        }

        auto v1 = Core::make_vertex(p1, n1);
        auto v2 = Core::make_vertex(p2, n2);
        auto v3 = Core::make_vertex(p3, n3);

        Core::add_face(mesh, Core::make_face(v1, v2, v3));
    }

    auto wrapper = Mesh(mesh);
    wrapper.setMaterial(material);

    // clear state
    vPoses.clear();
    vNorms.clear();
    faces.clear();

    return std::move(wrapper);
}
