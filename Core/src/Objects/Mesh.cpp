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
    mesh.boundingSphereDirtyFlag = true;

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
    mesh.boundingSphereDirtyFlag = true;
    return push_back(mesh.faces, face);
}

static Sphere boundedSphere(Sphere first, Sphere second)
{
    double r1 = first.radius;
    double r2 = second.radius;

    Vec dir = second.position - first.position;
    double d = length(dir);
    normalize(dir);

    if (d + r2 <= r1)
        return first;
    else if (d + r1 <= r2)
        return second;

    double r = (r1 + r2 + d) / 2;
    Vec pos = first.position + (d + r2 - r) * dir;
    return make_sphere(pos, r);
}

static Sphere boundedSphere(const Face& face)
{
    Vec A = face.verts[0].position;
    Vec B = face.verts[1].position;
    Vec C = face.verts[2].position;

    double a = length(B - C);
    double b = length(A - C);
    double c = length(A - B);

    if (a > c)
    {
        std::swap(a, c);
        std::swap(A, C);
    }
    if (b > c)
    {
        std::swap(b, c);
        std::swap(B, C);
    }

    Vec pos = (A + C) / 2;
    double radius = b / 2;

    if (a * a + b * b > c * c)
        radius = length(B - pos);

    return make_sphere(pos, radius);
}

void Core::recalc_bounding_sphere(Mesh& mesh)
{
    if (mesh.faces.size == 0)
        mesh.boundingSphere = make_sphere(make_pos(0, 0, 0), 0);
    if (mesh.faces.size == 1)
        mesh.boundingSphere = boundedSphere(mesh.faces.data[0]);

    Sphere first = boundedSphere(mesh.faces.data[0]);
    Sphere second = boundedSphere(mesh.faces.data[1]);

    for (size_t i = 2; i < mesh.faces.size; i++)
    {
        first = boundedSphere(first, second);
        second = boundedSphere(mesh.faces.data[i]);
    }

    mesh.boundingSphere = boundedSphere(first, second);
    mesh.boundingSphere.position = mesh.model_mat * mesh.boundingSphere.position;
}

Sphere Core::get_bounding_sphere(Mesh& mesh)
{
    if (mesh.boundingSphereDirtyFlag)
    {
        recalc_bounding_sphere(mesh);
        mesh.boundingSphereDirtyFlag = false;
    }

    return mesh.boundingSphere;
}

StatusCode Core::renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const Mesh& mesh, Camera& camera, LightingModelType lighting, FaceCullingType cullingType, ColorComputeFn colorComputeFn)
{
    if (!mesh.visible)
        return StatusCode::Success;

    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        Face face;

        if (!get(mesh.faces, i, face))
            return StatusCode::MemoryError;
        else if (!culling(face, camera, cullingType))
        {
            StatusCode result = renderFace(renderTarget, zbuffer, mesh, face, camera, lighting, colorComputeFn);
            if (result != StatusCode::Success)
                return result;
        }
    }

    return StatusCode::Success;
}

/*
StatusCode Core::renderMesh(RenderTarget& renderTarget, ZBuffer& zbuffer, const RectF& renderViewport, const Mesh& mesh, Camera& camera, LightingModelType lighting, FaceCullingType cullingType, ColorComputeFn colorComputeFn)
{
    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);

        if (!culling(*face, camera, renderViewport, cullingType))
        {
            StatusCode result = renderFace(renderTarget, zbuffer, renderViewport, mesh, *face, camera, lighting, colorComputeFn);
            if (result != StatusCode::Success)
                return result;
        }
    }

    return StatusCode::Success;
}
*/

StatusCode Core::renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera, Color color, FaceCullingType cullingType)
{
    return renderWireframeMesh(renderTarget, mesh, camera, to_pixel(color), cullingType);
}

StatusCode Core::renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, Camera& camera, Pixel color, FaceCullingType cullingType)
{
    if (!mesh.wireframe)
        return StatusCode::Success;

    recalc_mvp(camera, mesh.model_mat);

    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        Face face;
        if (!get(mesh.faces, i, face))
            return StatusCode::MemoryError;
        else if (!culling(face, camera, cullingType))
        {
            StatusCode result = renderWireframeFace(renderTarget, face, camera, color);
            if (result != StatusCode::Success)
                return result;
        }
    }

    return StatusCode::Success;
}
