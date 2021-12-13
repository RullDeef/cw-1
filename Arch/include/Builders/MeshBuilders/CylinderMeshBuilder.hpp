//
// Created by rulldeef on 12/12/21.
//

#ifndef CYLINDERMESHBUILDER_HPP
#define CYLINDERMESHBUILDER_HPP

#include "Builders/BaseMeshBuilder.hpp"
#include "Math/Color.hpp"

class CylinderMeshBuilder : public BaseMeshBuilder
{
public:
    CylinderMeshBuilder& setRadius(double newRadius);
    CylinderMeshBuilder& setHeight(double newHeight);
    CylinderMeshBuilder& setColor(const Color& newColor);
    CylinderMeshBuilder& setSmooth(bool smooth);
    CylinderMeshBuilder& setMeshDensity(int newEdgeCount);

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

#endif //CYLINDERMESHBUILDER_HPP
