#ifndef FACE_HPP
#define FACE_HPP

#include "Core/common/StatusCodes.hpp"
#include "Core/common/Color.hpp"
#include "Core/containers/arr_t.hpp"
#include "Core/math/Mat.hpp"
#include "Core/RenderTarget/RenderTarget.hpp"
#include "Core/RenderTarget/ZBuffer.hpp"
#include "Core/Objects/Vertex.hpp"
#include "Core/Objects/Light.hpp"


namespace Core
{
    struct RenderParams;
    struct Mesh;
    struct Camera;

    enum struct LightingModelType;

    using FaceCullingType = unsigned int;
    constexpr FaceCullingType OcclusionCullingType = 1 << 0;
    constexpr FaceCullingType BackfaceCullingType = 1 << 1;

    struct Face
    {
        Vertex verts[3];
    };

    Face make_face();
    Face make_face(const Vertex& v1, const Vertex& v2, const Vertex& v3);
    Face make_face(const Vertex* vArr);

    bool isValid(const Face& face);

    void recalc_normal(Face& face);

    Face operator*(const Mat& mat, const Face& face);

    Face project_viewport_frustrum(const Face& face, const Camera& camera);
    Face project_frustrum(const Face& face, const Camera& camera);
    Face project(const Face& face, const Camera& camera);

    Face unproject_frustrum(const Face& face, const Camera& camera);

    arr_t<Face, 4> clip_face(const Face& face, double x_aspect = 1.0, double y_aspect = 1.0);

    bool culling(const Face& face, const Camera& camera, FaceCullingType type);

    StatusCode renderFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face, const Camera &camera, LightingModelType lighting, ColorComputeFn colorComputeFn);
    StatusCode renderClippedFace(RenderTarget &renderTarget, ZBuffer &zbuffer, const Mesh &mesh, Face face, const Camera &camera, LightingModelType lighting, ColorComputeFn colorComputeFn);

    StatusCode renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera, Color color);
    StatusCode renderWireframeFace(RenderTarget& renderTarget, Face face, const Camera& camera, Pixel color);
}

#endif // FACE_HPP
