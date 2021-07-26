#ifndef OBJECTADAPTER_HPP
#define OBJECTADAPTER_HPP

#include "IObject.hpp"


enum class AdapterPolicy
{
    StrongOwnership,
    WeakOwnership
};

template<typename T>
class ObjectAdapter : public IObject
{
public:
    ObjectAdapter(size_t id, T adaptee, AdapterPolicy policy);
    virtual ~ObjectAdapter() = default;

    T& getAdaptee();
    const T& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;

private:
    T adaptee;
    AdapterPolicy policy;
};

#include "ObjectAdapterImp.hpp"
#include "Adapters/MeshAdapter.hpp"

#endif // OBJECTADAPTER_HPP
