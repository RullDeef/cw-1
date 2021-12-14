#ifndef LIGHTADAPTER_HPP
#define LIGHTADAPTER_HPP

#include "Objects/ObjectAdapter.hpp"
#include "Objects/Light.hpp"


template<>
class ObjectAdapter<Light> : public IObject
{
public:
    ObjectAdapter(size_t id, Light light);
    virtual ~ObjectAdapter() = default;

    Light& getAdaptee();
    const Light& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;
    virtual bool intersects(double& t, const Ray& ray) override;

protected:
    void onVisibilityChange() override;
    void onSelectionChange() override;
    void onTransformChange() override;

private:
    Light light;
};

#endif // LIGHTADAPTER_HPP
