#ifndef TRANSFORMER_HPP
#define TRANSFORMER_HPP

#include "Visitors/IObjectVisitor.hpp"


class Transformer : public IObjectVisitor
{
public:
    Transformer(double dx, double dy, double dz);

    void visit(ObjectAdapter<Core::Mesh>& mesh) override;
    void visit(ObjectAdapter<Core::Camera>& camera) override;
    void visit(ObjectAdapter<Core::Light>& lightSource) override;

private:
    double dx;
    double dy;
    double dz;
};

#endif // TRANSFORMER_HPP
