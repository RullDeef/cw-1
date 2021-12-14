#ifndef MESHADAPTER_HPP
#define MESHADAPTER_HPP

#include "Objects/Mesh.hpp"
#include "Objects/ObjectAdapter.hpp"


template<>
class ObjectAdapter<Mesh> : public IObject
{
public:
    ObjectAdapter(size_t id, Mesh mesh);
    virtual ~ObjectAdapter();

    Mesh& getAdaptee();
    const Mesh& getAdaptee() const;

    virtual void accept(IObjectVisitor& visitor) override;

    virtual bool intersects(double& t, const Ray& ray) override;

protected:
    void onVisibilityChange() override;
    void onSelectionChange() override;
    void onTransformChange() override;

private:
    Mesh mesh;
};

#endif // MESHADAPTER_HPP
