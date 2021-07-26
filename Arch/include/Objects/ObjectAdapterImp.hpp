#include "Objects/ObjectAdapter.hpp"
#include "Visitors/IObjectVisitor.hpp"


template<typename T>
ObjectAdapter<T>::ObjectAdapter(size_t id, T adaptee, AdapterPolicy policy)
    : adaptee(adaptee), IObject(id), policy(policy)
{
}

template<typename T>
T& ObjectAdapter<T>::getAdaptee()
{
    return adaptee;
}

template<typename T>
const T& ObjectAdapter<T>::getAdaptee() const
{
    return adaptee;
}

template<typename T>
void ObjectAdapter<T>::accept(IObjectVisitor& visitor)
{
    visitor.visit(*this);
}
