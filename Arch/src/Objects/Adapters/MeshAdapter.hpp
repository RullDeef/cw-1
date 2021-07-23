#ifndef MESHADAPTER_HPP
#define MESHADAPTER_HPP

#include "Mesh.hpp"
#include "ObjectAdapter.hpp"


template<>
class ObjectAdapter<Core::Mesh> : public IObject
{
public:
    ObjectAdapter(size_t id, Core::Mesh mesh, AdapterPolicy policy);
    virtual ~ObjectAdapter();

    Core::Mesh& getAdaptee();
    const Core::Mesh& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;

private:
    Core::Mesh mesh;
    AdapterPolicy policy;
};

#endif // MESHADAPTER_HPP
