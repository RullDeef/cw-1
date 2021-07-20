#ifndef OBJECTADAPTER_HPP
#define OBJECTADAPTER_HPP

#include "IObject.hpp"



enum class AdapterPolicy
{
    StrongOwnership,
    WeakOwnership
};

template<typename T, AdapterPolicy policy = AdapterPolicy::StrongOwnership>
class ObjectAdapter : public IObject
{
public:
    explicit ObjectAdapter(T& adaptee);
    virtual ~ObjectAdapter();

    T& getAdaptee();
    const T& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;

private:
    T* adaptee;
};

#include "ObjectAdapterImp.hpp"

#endif // OBJECTADAPTER_HPP
