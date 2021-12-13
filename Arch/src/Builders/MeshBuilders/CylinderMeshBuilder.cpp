//
// Created by rulldeef on 12/12/21.
//

#include "Builders/MeshBuilders/CylinderMeshBuilder.hpp"


CylinderMeshBuilder &CylinderMeshBuilder::setRadius(double newRadius)
{
    if (newRadius <= 0)
        throw std::runtime_error("bad cylinder radius");

    radius = newRadius;
    return *this;
}

CylinderMeshBuilder &CylinderMeshBuilder::setHeight(double newHeight)
{
    if (newHeight <= 0)
        throw std::runtime_error("bad cylinder height");

    height = newHeight;
    return *this;
}

CylinderMeshBuilder &CylinderMeshBuilder::setColor(const Color &newColor)
{
    color = newColor;
    return *this;
}

CylinderMeshBuilder &CylinderMeshBuilder::setSmooth(bool smooth)
{
    smoothEnabled = smooth;
    return *this;
}

CylinderMeshBuilder &CylinderMeshBuilder::setMeshDensity(int newEdgeCount)
{
    if (newEdgeCount < 3)
        throw std::runtime_error("bad cylinder edge count");

    edgeCount = newEdgeCount;
    return *this;
}

Mesh CylinderMeshBuilder::buildMesh()
{
    for (auto iy : std::initializer_list<std::pair<int, double>>{{0, -height/2}, {1, height/2}})
    {
        int i = iy.first;
        double y = iy.second;

        double x = radius;
        double z = 0;

        pushPos(Vector(x, y, z, 1.0));
        if (smoothEnabled)
            pushNorm(Vector(x, 0, z, 0.0).normalized());

        double u = 1.0 / edgeCount;
        x = radius * std::cos(u * 2 * M_PI);
        z = -radius * std::sin(u * 2 * M_PI);

        pushPos(Vector(x, y, z, 1.0));
        if (smoothEnabled)
            pushNorm(Vector(x, 0, z, 0.0).normalized());

        for (int iu = 2; iu < edgeCount; iu++)
        {
            u = double(iu) / edgeCount;
            x = radius * std::cos(u * 2 * M_PI);
            z = -radius * std::sin(u * 2 * M_PI);

            pushPos(Vector(x, y, z, 1.0));
            if (smoothEnabled)
                pushNorm(Vector(x, 0, z, 0.0).normalized());

            if (i == 0)
                linkFace(i * edgeCount,  i * edgeCount + iu, i * edgeCount + iu - 1);
            else
                linkFace(i * edgeCount,  i * edgeCount + iu - 1, i * edgeCount + iu);
        }
    }

    for (int i = 0; i < edgeCount; i++)
    {
        int p1 = i;
        int p2 = (i + 1) % edgeCount;
        int p3 = (i + 1) % edgeCount + edgeCount;
        int p4 = i + edgeCount;

        if (smoothEnabled)
        {
            linkFace(p1, p2, p3, p1, p2, p3);
            linkFace(p1, p3, p4, p1, p3, p4);
        }
        else
        {
            linkFace(p1, p2, p3);
            linkFace(p1, p3, p4);
        }
    }

    Material material;
    material.setAmbientColor(color);
    material.setSpecularColor(color);
    material.setDiffuseColor(color);
    useMaterial(material);

    return BaseMeshBuilder::buildMesh();
}
