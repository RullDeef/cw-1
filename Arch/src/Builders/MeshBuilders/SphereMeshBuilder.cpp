//
// Created by rulldeef on 11/29/21.
//

#include "Builders/MeshBuilders/SphereMeshBuilder.hpp"

SphereMeshBuilder &SphereMeshBuilder::setRadius(double newRadius)
{
    if (newRadius <= 0.0)
        throw std::runtime_error("invalid sphere radius");

    radius = newRadius;
    return *this;
}

SphereMeshBuilder &SphereMeshBuilder::setColor(const Color &newColor)
{
    color = newColor;
    return *this;
}

SphereMeshBuilder &SphereMeshBuilder::setSmooth(bool smooth)
{
    smoothEnabled = smooth;
    return *this;
}

SphereMeshBuilder& SphereMeshBuilder::setMeshDensity(int newVertsPerEdge)
{
    if (newVertsPerEdge <= 0)
        throw std::runtime_error("bad verts resolution");

    vertsPerEdge = newVertsPerEdge;
    return *this;
}

static Vector cubeToSphereTransform(const Vector& v) noexcept
{
    double xx = v.getX() * v.getX();
    double yy = v.getY() * v.getY();
    double zz = v.getZ() * v.getZ();

    double x = v.getX() * sqrt(1 - 0.5 * (yy + zz) + yy * zz / 3);
    double y = v.getY() * sqrt(1 - 0.5 * (zz + xx) + zz * xx / 3);
    double z = v.getZ() * sqrt(1 - 0.5 * (xx + yy) + xx * yy / 3);

    return Vector(x, y, z, 0.0);
}

Mesh SphereMeshBuilder::buildMesh()
{
    Vector sides[] = {Vector( 1, 0, 0, 0), Vector(0,  1, 0, 0),
                      Vector(-1, 0, 0, 0), Vector(0, -1, 0, 0),
                      Vector(0,  1, 0, 0), Vector(0, 0, 1, 0),
                      Vector(0, -1, 0, 0), Vector(0, 0, -1, 0),
                      Vector(0, 0,  1, 0), Vector(1, 0, 0, 0),
                      Vector(0, 0, -1, 0), Vector(-1, 0, 0, 0)};

    size_t fi = 0, ni = 0;
    for (size_t i = 0; i < 6; i++)
    {
        Vector xn = sides[2*i], yn = sides[2*i + 1], zn = xn.cross(yn);

        for (int iu = -vertsPerEdge; iu < vertsPerEdge; iu++)
        {
            double u = double(iu) / vertsPerEdge;
            double up1 = double(iu + 1) / vertsPerEdge;

            for (int iv = -vertsPerEdge; iv < vertsPerEdge; iv++)
            {
                double v = double(iv) / vertsPerEdge;
                double vp1 = double(iv + 1) / vertsPerEdge;

                Vector p1 = cubeToSphereTransform(xn + u * yn   + v * zn);
                Vector p2 = cubeToSphereTransform(xn + up1 * yn + v * zn);
                Vector p3 = cubeToSphereTransform(xn + u * yn   + vp1 * zn);
                Vector p4 = cubeToSphereTransform(xn + up1 * yn + vp1 * zn);

                pushPos(Vector(0, 0, 0, 1) + radius * p1);
                pushPos(Vector(0, 0, 0, 1) + radius * p2);
                pushPos(Vector(0, 0, 0, 1) + radius * p3);
                pushPos(Vector(0, 0, 0, 1) + radius * p4);

                if (smoothEnabled)
                {
                    pushNorm(p1);
                    pushNorm(p2);
                    pushNorm(p3);
                    pushNorm(p4);

                    linkFace(fi + 0, fi + 1, fi + 2, fi + 0, fi + 1, fi + 2);
                    linkFace(fi + 1, fi + 3, fi + 2, fi + 1, fi + 3, fi + 2);
                }
                else
                {
                    pushNorm((p1 + p2 + p3 + p4) / 4);

                    linkFace(fi + 0, fi + 1, fi + 2, ni);
                    linkFace(fi + 1, fi + 3, fi + 2, ni);

                    ni++;
                }

                fi += 4;
            }
        }
    }

    Material material;
    material.setAmbientColor(color);
    material.setSpecularColor(color);
    material.setDiffuseColor(color);
    useMaterial(material);

    return BaseMeshBuilder::buildMesh();
}
