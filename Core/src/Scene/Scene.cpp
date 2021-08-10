#include "Core/Scene/Scene.hpp"

using namespace Core;


Scene Core::make_scene()
{
    Scene scene{};

    scene.meshList = make_list<Mesh>();
    scene.lightList = make_vect<Light>(5);

    return scene;
}

void Core::clear_scene(Scene& scene)
{
    destroy(scene.meshList);
    scene.meshList = make_list<Mesh>();
    scene.lightList.size = 0;
}

void Core::append(Scene& scene, const Mesh& mesh)
{
    push_back(scene.meshList, mesh);
}

void Core::append(Scene& scene, const Light& light)
{
    push_back(scene.lightList, light);
}

void Core::destroy(Scene& scene)
{
    destroy(scene.meshList);
    destroy(scene.lightList);
}
