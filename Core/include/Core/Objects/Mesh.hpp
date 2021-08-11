#ifndef MESH_HPP
#define MESH_HPP

#include "Core/math/Vec.hpp"
#include "Core/math/Mat.hpp"
#include "Core/containers/vect_t.hpp"
#include "Core/Objects/Face.hpp"
#include "Core/Objects/Material.hpp"


namespace Core
{
    struct Mesh
    {
        Mat model_mat;
        Material material;
        vect_t<Face> faces;

        bool visible;
        bool wireframe;
    };

    Mesh make_mesh(size_t faces_count);
    Mesh make_mesh(size_t faces_count, const Material& material);
    void destroy(Mesh& mesh);

    bool add_face(Mesh& mesh, const Face& face);

    StatusCode renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera, LightingModelType lighting, FaceCullingType cullingType, ColorComputeFn colorComputeFn);

    StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera, Color color, FaceCullingType cullingType);
    StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera, Pixel color, FaceCullingType cullingType);
}

#endif // MESH_HPP
