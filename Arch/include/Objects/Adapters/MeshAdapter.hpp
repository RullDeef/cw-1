#ifndef MESHADAPTER_HPP
#define MESHADAPTER_HPP

#include "Core/Objects/Mesh.hpp"
#include "Objects/ObjectAdapter.hpp"


template<>
class ObjectAdapter<Core::Mesh> : public IObject
{
public:
    ObjectAdapter(size_t id, Core::Mesh mesh, AdapterPolicy policy);
    virtual ~ObjectAdapter();

    Core::Mesh& getAdaptee();
    const Core::Mesh& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;

    virtual bool intersects(double& t, const Core::Ray& ray) override;

private:
    Core::Mesh mesh;
    AdapterPolicy policy;
};

#endif // MESHADAPTER_HPP
