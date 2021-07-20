#include "ObjectAdapter.hpp"
#include "IObjectVisitor.hpp"


template<typename T, AdapterPolicy policy>
ObjectAdapter<T, policy>::ObjectAdapter(T& adaptee)
    : adaptee(&adaptee)
{
}

template<typename T, AdapterPolicy policy>
ObjectAdapter<T, policy>::~ObjectAdapter()
{
    constexpr if (policy == AdapterPolicy::StrongOwnership)
        delete adaptee;
}

template<typename T, AdapterPolicy policy>
T& ObjectAdapter<T, policy>::getAdaptee()
{
    return *adaptee;
}

template<typename T, AdapterPolicy policy>
const T& ObjectAdapter<T, policy>::getAdaptee() const
{
    return *adaptee;
}

template<typename T, AdapterPolicy policy>
void ObjectAdapter<T, policy>::accept(IObjectVisitor& visitor)
{
    visitor->visit(*this);
}

