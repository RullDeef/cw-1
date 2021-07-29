#ifndef FACE_HPP
#define FACE_HPP

#include "Core/Objects/Vertex.hpp"


namespace Core
{
    struct Face
    {
        Vertex verts[3];
    };

    Face make_face();
    Face make_face(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    Face make_face(const Vertex* vArr);

    bool isValid(const Face& face);

    void recalc_normal(Face& face);
}

#endif // FACE_HPP
