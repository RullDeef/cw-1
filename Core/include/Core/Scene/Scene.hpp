#ifndef SCENE_HPP
#define SCENE_HPP

#include "Core/containers/list_t.hpp"
#include "Core/containers/vect_t.hpp"
#include "Core/Objects/Mesh.hpp"
#include "Core/Objects/Light.hpp"


namespace Core
{
    struct Scene
    {
        list_t<Mesh> meshList;
        vect_t<Light> lightList;
    };

    Scene make_scene();

    void clear_scene(Scene& scene);

    void append(Scene& scene, const Mesh& mesh);
    void append(Scene& scene, const Light& light);

    void destroy(Scene& scene);
}

#endif // SCENE_HPP
