#include "Core/Objects/Material.hpp"

using namespace Core;


Material Core::make_material()
{
    Material mat{};

    mat.ambientColor = Colors::white;
    mat.diffuseColor = Colors::white;
    mat.specularColor = Colors::white;

    mat.opacity = 1.0;
    mat.specularHighlight = 1.0;

    return mat;
}
