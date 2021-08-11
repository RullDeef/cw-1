#include "Core/Objects/Camera.hpp"
#include "Core/Objects/Mesh.hpp"

using namespace Core;


Mesh Core::make_mesh(size_t faces_count)
{
    Mesh mesh{};

    mesh.model_mat = make_mat_id();
    mesh.material = make_material();
    mesh.faces = make_vect<Face>(faces_count);

    mesh.visible = true;
    mesh.wireframe = false;

    return mesh;
}

Mesh Core::make_mesh(size_t faces_count, const Material& material)
{
    Mesh mesh = make_mesh(faces_count);

    mesh.material = material;

    return mesh;
}

void Core::destroy(Mesh& mesh)
{
    destroy(mesh.faces);
}

bool Core::add_face(Mesh &mesh, const Face &face)
{
    return push_back(mesh.faces, face);
}

StatusCode Core::renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera, LightingModelType lighting, FaceCullingType cullingType, ColorComputeFn colorComputeFn)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);

        if (!culling(*face, camera, cullingType))
        {
            StatusCode result = renderFace(renderTarget, zbuffer, mesh, *face, camera, lighting, colorComputeFn);
            if (result != StatusCode::Success)
                return result;
        }
    }

    return StatusCode::Success;
}

StatusCode Core::renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera, Color color, FaceCullingType cullingType)
{
    return renderWireframeMesh(renderTarget, mesh, camera, to_pixel(color), cullingType);
}

StatusCode Core::renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera, Pixel color, FaceCullingType cullingType)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);

        if (!culling(*face, camera, cullingType))
        {
            StatusCode result = renderWireframeFace(renderTarget, *face, camera, color);
            if (result != StatusCode::Success)
                return result;
        }
    }

    return StatusCode::Success;
}
