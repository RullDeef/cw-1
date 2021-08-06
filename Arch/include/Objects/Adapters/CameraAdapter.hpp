#ifndef CAMERAADAPTER_HPP
#define CAMERAADAPTER_HPP

#include "Math/Ray.hpp"
#include "Objects/Camera.hpp"
#include "Objects/ObjectAdapter.hpp"


template<>
class ObjectAdapter<Camera> : public IObject
{
public:
    ObjectAdapter(size_t id, Camera camera);
    virtual ~ObjectAdapter() = default;

    Camera& getAdaptee();
    const Camera& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;
    virtual bool intersects(double& t, const Ray& ray) override;

private:
    Camera camera;
};

#endif // CAMERAADAPTER_HPP
