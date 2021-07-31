#ifndef MESH_HPP
#define MESH_HPP

#include "Core/common/math/Vec.hpp"
#include "Core/common/math/Mat.hpp"
#include "Core/common/containers/vect_t.hpp"
#include "Core/Objects/Face.hpp"
#include "Core/Objects/Material.hpp"


namespace Core
{
    struct Mesh
    {
        Mat model_mat;
        Material material;
        vect_t<Face> faces;
    };

    Mesh make_mesh(size_t faces_count);
    Mesh make_mesh(size_t faces_count, const Material& material);
    void destroy(Mesh& mesh);

    bool add_face(Mesh& mesh, const Face& face);
}

#endif // MESH_HPP
