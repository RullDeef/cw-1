#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include "Visitors/IObjectVisitor.hpp"


class Transformer : public IObjectVisitor
{
public:
    Transformer(double dx, double dy, double dz);

    void visit(ObjectAdapter<Mesh>& mesh) override;
    void visit(ObjectAdapter<Camera>& camera) override;
    void visit(ObjectAdapter<Light>& lightSource) override;

private:
    double dx;
    double dy;
    double dz;
};

#endif // TRANSFORMER_HPP
