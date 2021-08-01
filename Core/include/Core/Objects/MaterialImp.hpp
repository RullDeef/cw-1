#ifndef MATERIALIMP_HPP
#define MATERIALIMP_HPP

#include "Core/Objects/Material.hpp"


namespace Core
{
    template<size_t lightCount>
    Color compute_color(const Material& material, const arr_t<Light, lightCount>& lights, const Vec& view, const Vec& normal)
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
}

#endif // MATERIALIMP_HPP
