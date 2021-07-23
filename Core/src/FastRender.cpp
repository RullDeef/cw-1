#include "FastRender.hpp"
#include "LineRenderer.hpp"
#include "Mat.hpp"

using namespace Core;

static void makeBG(RenderTarget& renderTarget);
static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, const Camera& camera);
static StatusCode renderFace(RenderTarget& renderTarget, const Face& face, const Camera& camera);
static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2);
static bool backFaceCooling(const Face& face);


StatusCode Core::fastRenderScene(RenderParams renderParams)
{
    makeBG(renderParams.renderTarget);

    for (auto node = renderParams.scene.meshList.head; node; node = node->next)
        renderWireframeMesh(renderParams.renderTarget, node->value, renderParams.camera);

    return StatusCode::Success;
}

static void makeBG(RenderTarget& renderTarget)
{
    for (size_t row = 0; row < renderTarget.height; row++)
    {
        for (size_t col = 0; col < renderTarget.width; col++)
        {
            if (((row / 64) % 2 == 0) ^ ((col / 64) % 2 == 0))
                setPixel(renderTarget, row, col, Color::black);
            else
                setPixel(renderTarget, row, col, { 64u, 0u, 64u, 255u });
        }
    }
}

static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, const Camera& camera)
{
    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);
        renderFace(renderTarget, *face, camera);
    }

    return StatusCode::Success;
}

static StatusCode renderFace(RenderTarget& renderTarget, const Face& face, const Camera& camera)
{
    if (backFaceCooling(face))
        return StatusCode::Success;

    Vec p1 = project_point(camera, face.verts[0].position);
    Vec p2 = project_point(camera, face.verts[1].position);
    Vec p3 = project_point(camera, face.verts[2].position);

    renderLine(renderTarget, p1, p2);
    renderLine(renderTarget, p2, p3);
    renderLine(renderTarget, p3, p1);

    return StatusCode::Success;
}

static bool backFaceCooling(const Face& face)
{
    Vec norm = Core::cross(face.verts[1].position - face.verts[0].position, face.verts[2].position - face.verts[0].position);
    double dot = Core::dot(Core::make_dir(0,0, 1), norm);
    return dot < 0.0;
}

static StatusCode renderLine(RenderTarget& renderTarget, const Vec& p1, const Vec& p2)
{
    return renderLine(renderTarget, p1.x, p1.y, p2.x, p2.y, Color::green);
}
