#include "Objects/Material.hpp"


Material::Material(const Core::Material &mat)
    : ambientColor(mat.ambientColor), diffuseColor(mat.diffuseColor),
      specularColor(mat.specularColor), specularHighlight(mat.specularHighlight),
      opacity(mat.opacity)
{
}

Material::operator Core::Material() const
{
    auto mat = Core::make_material();

    mat.ambientColor = ambientColor;
    mat.diffuseColor = diffuseColor;
    mat.specularColor = specularColor;
    mat.specularHighlight = specularHighlight;
    mat.opacity = opacity;

    return mat;
}
