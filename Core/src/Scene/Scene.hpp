#ifndef SCENE_HPP
#define SCENE_HPP

#include "list_t.hpp"
#include "Mesh.hpp"


namespace Core
{
    struct Scene
    {
        list_t<Mesh> meshList;
    };
}

#endif // SCENE_HPP
