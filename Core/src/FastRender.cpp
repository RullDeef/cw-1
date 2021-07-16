#include "FastRender.hpp"
#include "LineRenderer.hpp"

using namespace Core;

static void makeBG(RenderTarget& renderTarget);
static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, const mat& camera_mat);
static StatusCode renderFace(RenderTarget& renderTarget, const Face& face, const mat& camera_mat);
static StatusCode renderLine(RenderTarget& renderTarget, screen_point p1, screen_point p2);


StatusCode Core::fastRenderScene(RenderTarget& renderTarget, const Scene& scene, const Camera& camera)
{
    makeBG(renderTarget);

    mat camera_mat = get_camera_mat(camera, renderTarget.width, renderTarget.height);
    for (auto node = scene.meshList.head; node; node = node->next)
        renderWireframeMesh(renderTarget, node->value, camera_mat);

    // renderLine(renderTarget, 10, 20, 300, 400, Color::green);
    // renderLine(renderTarget, 30, 20, 300, 400, Color::green);
    // renderLine(renderTarget, 10, 60, 300, 400, Color::green);

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

static StatusCode renderWireframeMesh(RenderTarget& renderTarget, const Mesh& mesh, const mat& camera_mat)
{
    for (size_t i = 0; i < mesh.faces.size; i++)
    {
        const Face* face;
        at(mesh.faces, i, face);
        renderFace(renderTarget, *face, camera_mat);
    }

    return StatusCode::Success;
}

static StatusCode renderFace(RenderTarget& renderTarget, const Face& face, const mat& camera_mat)
{
    screen_point p1, p2;

    viewport vp = viewport_init(renderTarget.width, renderTarget.height);

    p1 = vec_project(face.verts[0].position, camera_mat, vp);
    p2 = vec_project(face.verts[1].position, camera_mat, vp);
    renderLine(renderTarget, p1, p2);

    p1 = vec_project(face.verts[1].position, camera_mat, vp);
    p2 = vec_project(face.verts[2].position, camera_mat, vp);
    renderLine(renderTarget, p1, p2);

    p1 = vec_project(face.verts[2].position, camera_mat, vp);
    p2 = vec_project(face.verts[0].position, camera_mat, vp);
    renderLine(renderTarget, p1, p2);

    return StatusCode::Success;
}

static StatusCode renderLine(RenderTarget& renderTarget, screen_point p1, screen_point p2)
{
    return renderLine(renderTarget, p1.x, p1.y, p2.x, p2.y, Color::green);
}
