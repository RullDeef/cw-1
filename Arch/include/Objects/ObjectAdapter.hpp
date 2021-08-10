#ifndef OBJECTADAPTER_HPP
#define OBJECTADAPTER_HPP

#include "IObject.hpp"


template<typename T>
class ObjectAdapter : public IObject
{
public:
    ObjectAdapter(size_t id, T adaptee);
    virtual ~ObjectAdapter() = default;

    T& getAdaptee();
    const T& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;
    virtual bool intersects(double& t, const Ray& ray) override;

private:
    T adaptee;
};

#include "ObjectAdapterImp.hpp"
#include "Adapters/MeshAdapter.hpp"

#endif // OBJECTADAPTER_HPP
