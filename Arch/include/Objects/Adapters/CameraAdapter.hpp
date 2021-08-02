#ifndef CAMERAADAPTER_HPP
#define CAMERAADAPTER_HPP

#include "Core/Objects/Camera.hpp"
#include "Objects/ObjectAdapter.hpp"


template<>
class ObjectAdapter<Core::Camera> : public IObject
{
public:
    ObjectAdapter(size_t id, Core::Camera camera, AdapterPolicy policy);
    virtual ~ObjectAdapter() = default;

    Core::Camera& getAdaptee();
    const Core::Camera& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;

    virtual bool intersects(double& t, const Core::Ray& ray) override;

private:
    Core::Camera camera;
    AdapterPolicy policy;
};


#endif // CAMERAADAPTER_HPP
