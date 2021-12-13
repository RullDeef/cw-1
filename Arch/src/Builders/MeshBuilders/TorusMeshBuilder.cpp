//
// Created by rulldeef on 12/12/21.
//

#include "Builders/MeshBuilders/TorusMeshBuilder.hpp"

TorusMeshBuilder &TorusMeshBuilder::setInnerRadius(double newRadius)
{
    if (newRadius <= 0.0)
        throw std::runtime_error("bad inner radius");

    innerRadius = newRadius;
    return *this;
}

TorusMeshBuilder &TorusMeshBuilder::setOuterRadius(double newRadius)
{
    if (newRadius <= 0.0)
        throw std::runtime_error("bad outer radius");

    outerRadius = newRadius;
    return *this;
}

TorusMeshBuilder &TorusMeshBuilder::setColor(const Color &newColor)
{
    color = newColor;
    return *this;
}

TorusMeshBuilder &TorusMeshBuilder::setSmooth(bool smooth)
{
    smoothEnabled = smooth;
    return *this;
}

TorusMeshBuilder &TorusMeshBuilder::setMeshDensity(int u, int v)
{
    if (u <= 0 || v <= 0)
        throw std::runtime_error("bad mesh density");

    vertsPerU = u;
    vertsPerV = v;
    return *this;
}

Mesh TorusMeshBuilder::buildMesh()
{
    if (outerRadius <= innerRadius)
        throw std::runtime_error("bad radius condition");

    size_t fi = 0;
    size_t ni = 0;

    for (int iu = 0; iu < vertsPerU; iu++)
    {
        double u = double(iu) / vertsPerU;
        double up1 = double(iu + 1) / vertsPerU;

        for (int iv = 0; iv < vertsPerV; iv++)
        {
            double v = double(iv) / vertsPerV;
            double vp1 = double(iv + 1) / vertsPerV;

            Vector p1 = getPosition(u, v);
            Vector p2 = getPosition(u, vp1);
            Vector p3 = getPosition(up1, v);
            Vector p4 = getPosition(up1, vp1);

            pushPos(p1);
            pushPos(p2);
            pushPos(p3);
            pushPos(p4);

            if (smoothEnabled)
            {
                pushNorm(getNormal(u, v));
                pushNorm(getNormal(u, vp1));
                pushNorm(getNormal(up1, v));
                pushNorm(getNormal(up1, vp1));

                linkFace(fi + 0, fi + 1, fi + 2, fi + 0, fi + 1, fi + 2);
                linkFace(fi + 1, fi + 3, fi + 2, fi + 1, fi + 3, fi + 2);
            }
            else
            {
                Vector norm = (p1 + p2 + p3 + p4) / 4;
                norm = Vector(norm.getX(), norm.getY(), norm.getZ(), 0.0);
                pushNorm(norm);

                linkFace(fi + 0, fi + 1, fi + 2, ni);
                linkFace(fi + 1, fi + 3, fi + 2, ni);

                ni++;
            }

            fi += 4;
        }
    }

    Material material;
    material.setAmbientColor(color);
    material.setSpecularColor(color);
    material.setDiffuseColor(color);
    useMaterial(material);

    return BaseMeshBuilder::buildMesh();
}

Vector TorusMeshBuilder::getPosition(double u, double v) const
{
    u *= 2 * M_PI;
    v *= 2 * M_PI;

    double x = (outerRadius + innerRadius * std::cos(v)) * std::cos(u);
    double y = innerRadius * std::sin(v);
    double z = (outerRadius + innerRadius * std::cos(v)) * std::sin(u);

    return Vector(x, y, z, 1.0);
}

Vector TorusMeshBuilder::getNormal(double u, double v) const
{
    u *= 2 * M_PI;
    v *= 2 * M_PI;

    double x = std::cos(u) * std::cos(v);
    double y = std::sin(u) * std::sin(u) * std::sin(v) + std::cos(u) * std::cos(u);
    double z = std::sin(u) * std::cos(v);

    return Vector(x, y, z, 0.0).normalized();
}
