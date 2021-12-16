#include "Objects/Material.hpp"


Material::Material() : Material(Core::make_material())
{
}

Material::Material(const Core::Material &mat)
    : ambientColor(mat.ambientColor), diffuseColor(mat.diffuseColor),
      specularColor(mat.specularColor), specularHighlight(mat.specularHighlight),
      opacity(mat.opacity), coefReflection(mat.coefReflection), coefRefraction(mat.coefRefraction),
      refractiveIndex(mat.refractiveIndex)
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

    mat.coefReflection = coefReflection;
    mat.coefRefraction = coefRefraction;
    mat.refractiveIndex = refractiveIndex;

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

void Material::setReflection(double value)
{
    coefReflection = value; /// TODO: checks
}

void Material::setRefraction(double value)
{
    coefRefraction = value; /// TODO: checks
}

void Material::setRefractionIndex(double value)
{
    refractiveIndex = value; /// TODO: checks
}
