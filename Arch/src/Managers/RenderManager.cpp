#include "Core.hpp"
#include "RenderManager.hpp"
#include <chrono>


void RenderManager::renderScene(Core::RenderTarget& renderTarget)
{
    Core::Scene scene;
    scene.meshList = Core::make_list<Core::Mesh>();

    Core::Mesh cube = Core::make_mesh(4);
    cube.faces.size = 4;
    {
        double time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000.0;
        Core::Mat model_mat = Core::make_mat_rotation(Core::make_dir(0, 1, 0), time);

        Core::Face face;
        face.verts[0].position = model_mat * Core::make_pos(2, -2, 0);
        face.verts[1].position = model_mat * Core::make_pos(-2, 2, 0);
        face.verts[2].position = model_mat * Core::make_pos(2,  2, 0);
        Core::set(cube.faces, 0, face);
        face.verts[0].position = model_mat * Core::make_pos(2, -2, 0.25);
        face.verts[1].position = model_mat * Core::make_pos(-2, 2, 0.25);
        face.verts[2].position = model_mat * Core::make_pos(2,  3, 0.25);
        Core::set(cube.faces, 1, face);
        face.verts[0].position = model_mat * Core::make_pos(2, -2, 0.5);
        face.verts[1].position = model_mat * Core::make_pos(-2, 2, 0.5);
        face.verts[2].position = model_mat * Core::make_pos(2,  4, 0.5);
        Core::set(cube.faces, 2, face);
        face.verts[0].position = model_mat * Core::make_pos(2, -2, 0.75);
        face.verts[1].position = model_mat * Core::make_pos(-2, 2, 0.75);
        face.verts[2].position = model_mat * Core::make_pos(2,  5, 0.75);
        Core::set(cube.faces, 3, face);
    }

    Core::append(scene.meshList, cube);

    Core::Rect viewport = Core::make_rect(renderTarget.width, renderTarget.height);

    Core::Camera camera = Core::make_camera(viewport);
    camera.model_mat = Core::make_mat_translation(Core::make_pos(0, 0, -10));
    Core::recalc_mvp(camera);

    Core::renderScene({
        renderTarget, scene, camera,
        Core::RenderParams::RenderType::FastRenderType,
        viewport
    });
}
