#ifndef FACE_HPP
#define FACE_HPP

#include "Core/Objects/Vertex.hpp"


namespace Core
{
    struct Camera;

    struct Face
    {
        Vertex verts[3];
    };

    Face make_face();
    Face make_face(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    Face make_face(const Vertex* vArr);

    bool isValid(const Face& face);

    void recalc_normal(Face& face);

    Face project(const Face& face, const Camera& camera);
}

#endif // FACE_HPP
