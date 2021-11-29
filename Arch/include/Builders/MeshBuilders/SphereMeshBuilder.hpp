//
// Created by rulldeef on 11/29/21.
//

#ifndef SPHEREMESHBUILDER_HPP
#define SPHEREMESHBUILDER_HPP

#include "Builders/BaseMeshBuilder.hpp"
#include "Math/Color.hpp"


class SphereMeshBuilder : public BaseMeshBuilder
{
public:
    SphereMeshBuilder& setRadius(double newRadius);
    SphereMeshBuilder& setColor(const Color& newColor);
    SphereMeshBuilder& setSmooth(bool smooth);
    SphereMeshBuilder& setMeshDensity(int newVertsPerEdge);

    virtual Mesh build() override;

protected:
    using BaseMeshBuilder::pushPos;
    using BaseMeshBuilder::pushNorm;
    using BaseMeshBuilder::linkFace;
    using BaseMeshBuilder::useMaterial;

private:
    double radius = 1.0;
    int vertsPerEdge = 10;
    Color color = Color::white();
    bool smoothEnabled = false;
};

#endif //SPHEREMESHBUILDER_HPP
