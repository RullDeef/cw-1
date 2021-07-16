#ifndef OBJECTADAPTER_HPP
#define OBJECTADAPTER_HPP

#include "IObject.hpp"


template<typename T>
class ObjectAdapter : public IObject
{
public:
    explicit ObjectAdapter(T& adaptee);
    virtual ~ObjectAdapter();

    T& getAdaptee();
    const T& getAdaptee() const;

    virtual accept(IObjectVisitor& visitor) override;

private:
    T* adaptee;
};

#endif // OBJECTADAPTER_HPP
