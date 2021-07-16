#include "Core.hpp"
#include "RenderManager.hpp"


void RenderManager::renderScene(Core::RenderTarget& renderTarget)
{
    Core::Scene scene;
    scene.meshList = Core::make_list<Core::Mesh>();

    Core::Mesh cube = Core::make_mesh(4);
    cube.faces.size = 4;
    {
        Core::Face face;
        face.verts[0].position = Core::vec_create(2, -2, 0);
        face.verts[1].position = Core::vec_create(-2, 2, 0);
        face.verts[2].position = Core::vec_create(2,  2, 0);
        Core::set(cube.faces, 0, face);
        face.verts[0].position = Core::vec_create(2, -2, 0.25);
        face.verts[1].position = Core::vec_create(-2, 2, 0.25);
        face.verts[2].position = Core::vec_create(2,  3, 0.25);
        Core::set(cube.faces, 1, face);
        face.verts[0].position = Core::vec_create(2, -2, 0.5);
        face.verts[1].position = Core::vec_create(-2, 2, 0.5);
        face.verts[2].position = Core::vec_create(2,  4, 0.5);
        Core::set(cube.faces, 2, face);
        face.verts[0].position = Core::vec_create(2, -2, 0.75);
        face.verts[1].position = Core::vec_create(-2, 2, 0.75);
        face.verts[2].position = Core::vec_create(2,  5, 0.75);
        Core::set(cube.faces, 3, face);
    }

    Core::append(scene.meshList, cube);

    Core::Camera camera = Core::make_camera();
    camera.model_mat = Core::mat_translation(Core::vec_create(0, 0, -10));

    Core::renderScene(renderTarget, scene, camera);
}
