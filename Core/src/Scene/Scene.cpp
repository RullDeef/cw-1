#include "Scene.hpp"

using namespace Core;


Scene Core::make_scene()
{
    Scene scene{};

    scene.meshList = make_list<Mesh>();

    return scene;
}

void Core::append(Scene& scene, const Mesh& mesh)
{
    append(scene.meshList, mesh);
}

void Core::destroy(Scene& scene)
{
    destroy(scene.meshList);
}
