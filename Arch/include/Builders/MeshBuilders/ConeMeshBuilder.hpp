//
// Created by rulldeef on 12/12/21.
//

#ifndef CONEMESHBUILDER_HPP
#define CONEMESHBUILDER_HPP

#include "Builders/BaseMeshBuilder.hpp"
#include "Math/Color.hpp"

class ConeMeshBuilder : public BaseMeshBuilder
{
public:
    ConeMeshBuilder& setRadius(double newRadius);
    ConeMeshBuilder& setHeight(double newHeight);
    ConeMeshBuilder& setColor(const Color& newColor);
    ConeMeshBuilder& setSmooth(bool smooth);
    ConeMeshBuilder& setMeshDensity(int newEdgeCount);

protected:
    Mesh buildMesh() override;

    using BaseMeshBuilder::pushPos;
    using BaseMeshBuilder::pushNorm;
    using BaseMeshBuilder::linkFace;
    using BaseMeshBuilder::useMaterial;

private:
    double radius = 1.0;
    double height = 1.0;

    int edgeCount = 6;

    Color color = Color::white();
    bool smoothEnabled = false;
};

#endif //CONEMESHBUILDER_HPP
