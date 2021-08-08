#ifndef SCENE_HPP
#define SCENE_HPP

#include "Core/containers/list_t.hpp"
#include "Core/Objects/Mesh.hpp"


namespace Core
{
    struct Scene
    {
        list_t<Mesh> meshList;
    };

    Scene make_scene();

    void append(Scene& scene, const Mesh& mesh);

    void destroy(Scene& scene);
}

#endif // SCENE_HPP
