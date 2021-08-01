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

Color compute_color(const Material& material, const vect_t<Light>& lights, const Vec& view, const Vec& normal)
{
    const double ambient = 0.1;
    Color color = ambient * material.ambientColor;

    for (size_t i = 0; i < lights.size; i++)
    {
        Light light;
        if (get(lights, i, light))
        {
            if (light.type == Light::Type::Ambient)
            {
                color += light.ambient.intensity * light.ambient.color;
            }
            else if (light.type == Light::Type::Directional)
            {
                Vec dir = light.directional.direction;
                Vec Rm = 2 * dot(-dir, normal) * normal + dir;

                double Lm_N = std::max(0.0, dot(-dir, normal));
                double Rm_V = std::max(0.0, dot(Rm, -view));
                Rm_V = std::pow(Rm_V, material.specularHighlight);

                color += material.diffuseColor * Lm_N + light.directional.color * Rm_V;
            }
        }
    }

    return color;
}
