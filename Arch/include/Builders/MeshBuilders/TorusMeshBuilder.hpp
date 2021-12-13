//
// Created by rulldeef on 12/12/21.
//

#ifndef TORUSMESHBUILDER_HPP
#define TORUSMESHBUILDER_HPP

#include "Builders/BaseMeshBuilder.hpp"
#include "Math/Color.hpp"


class TorusMeshBuilder : public BaseMeshBuilder
{
public:
    TorusMeshBuilder& setInnerRadius(double newRadius);
    TorusMeshBuilder& setOuterRadius(double newRadius);
    TorusMeshBuilder& setColor(const Color& newColor);
    TorusMeshBuilder& setSmooth(bool smooth);
    TorusMeshBuilder& setMeshDensity(int u, int v);

protected:
    Mesh buildMesh() override;

    using BaseMeshBuilder::pushPos;
    using BaseMeshBuilder::pushNorm;
    using BaseMeshBuilder::linkFace;
    using BaseMeshBuilder::useMaterial;

    Vector getPosition(double u, double v) const;
    Vector getNormal(double u, double v) const;

private:
    double innerRadius = 1.0;
    double outerRadius = 2.0;

    int vertsPerU = 10;
    int vertsPerV = 10;

    Color color = Color::white();
    bool smoothEnabled = false;
};

#endif //TORUSMESHBUILDER_HPP
