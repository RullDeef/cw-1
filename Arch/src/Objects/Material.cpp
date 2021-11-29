#include "Objects/Material.hpp"


Material::Material() : Material(Core::make_material())
{
}

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

void Material::setAmbientColor(const Color &color)
{
    ambientColor = color;
}

void Material::setDiffuseColor(const Color &color)
{
    diffuseColor = color;
}

void Material::setSpecularColor(const Color &color)
{
    specularColor = color;
}

void Material::setSpecularHighlight(double value)
{
    specularHighlight = value;
}

void Material::setOpacity(double value)
{
    opacity = value;
}
