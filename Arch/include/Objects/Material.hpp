#ifndef ARCH_MATERIAL_HPP
#define ARCH_MATERIAL_HPP

#include <Core/Objects/Material.hpp>
#include "Math/Color.hpp"


class Material
{
public:
    Material() = default;
    Material(const Core::Material& mat);

    [[nodiscard]] inline Color getAmbientColor() const { return ambientColor; }
    [[nodiscard]] inline Color getDiffuseColor() const { return diffuseColor; }
    [[nodiscard]] inline Color getSpecularColor() const { return specularColor; }

    [[nodiscard]] inline double getSpecularHighlight() const { return specularHighlight; }
    [[nodiscard]] inline double getOpacity() const { return opacity; }

    void setAmbientColor(const Color& color);
    void setDiffuseColor(const Color& color);
    void setSpecularColor(const Color& color);

    void setSpecularHighlight(double value);
    void setOpacity(double value);

    operator Core::Material() const;

private:
    Color ambientColor;
    Color diffuseColor;
    Color specularColor;

    double specularHighlight = 1.0;
    double opacity = 1.0;
};

#endif // ARCH_MATERIAL_HPP
