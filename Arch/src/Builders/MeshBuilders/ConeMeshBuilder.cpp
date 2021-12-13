//
// Created by rulldeef on 12/12/21.
//

#include "Builders/MeshBuilders/ConeMeshBuilder.hpp"


ConeMeshBuilder &ConeMeshBuilder::setRadius(double newRadius)
{
    if (newRadius <= 0.0)
        throw std::runtime_error("bad cone radius");

    radius = newRadius;
    return *this;
}

ConeMeshBuilder &ConeMeshBuilder::setHeight(double newHeight)
{
    if (newHeight <= 0.0)
        throw std::runtime_error("ad cone height");

    height = newHeight;
    return *this;
}

ConeMeshBuilder &ConeMeshBuilder::setColor(const Color &newColor)
{
    color = newColor;
    return *this;
}

ConeMeshBuilder &ConeMeshBuilder::setSmooth(bool smooth)
{
    smoothEnabled = smooth;
    return *this;
}

ConeMeshBuilder &ConeMeshBuilder::setMeshDensity(int newEdgeCount)
{
    if (newEdgeCount < 3)
        throw std::runtime_error("bad cone edge count");

    edgeCount = newEdgeCount;
    return *this;
}

Mesh ConeMeshBuilder::buildMesh()
{
    pushPos(Vector(0, height, 0, 1.0));

    double x = radius;
    double y = 0;
    double z = 0;

    pushPos(Vector(x, y, z, 1.0));
    if (smoothEnabled)
        pushNorm(Vector(x, y, z, 0.0).normalized());

    size_t in = 0;

    for (int iu = 1; iu <= edgeCount; iu++)
    {
        double u = double(iu) / edgeCount * 2 * M_PI;

        x = radius * std::cos(u);
        z = -radius * std::sin(u);

        pushPos(Vector(x, y, z, 1.0));
        if (smoothEnabled)
        {
            double x2 = radius * std::cos(double(iu + 1) / edgeCount * 2 * M_PI);
            double z2 = -radius * std::sin(double(iu + 1) / edgeCount * 2 * M_PI);

            pushNorm(Vector(x, y, z, 0.0).normalized());
            pushNorm(Vector(x2, y, z2, 0.0).normalized());
            pushNorm(Vector(x2, y, z2, 0.0).normalized());

            linkFace(0, iu - 1, iu, in, in + 1, in + 2);
            in += 3;
        }
        else
        {
            linkFace(0, iu - 1, iu);
        }


        if (iu > 1)
            linkFace(1, iu, iu - 1);
    }

    Material material;
    material.setAmbientColor(color);
    material.setSpecularColor(color);
    material.setDiffuseColor(color);
    useMaterial(material);

    return BaseMeshBuilder::buildMesh();
}
