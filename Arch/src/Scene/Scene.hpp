#ifndef ARCH_SCENE_HPP
#define ARCH_SCENE_HPP

#include <memory>
#include <list>
#include "Scene.hpp"
#include "../../Core/src/Scene/Scene.hpp"

class IObject;


class Scene
{
public:
    using objptr_t = std::shared_ptr<IObject>;
    using containter_t = std::list<objptr_t>;
    using iterator = containter_t::iterator;
    using const_iterator = containter_t::const_iterator;

public:
    Scene();
    virtual ~Scene();

    void insert(const_iterator pos, const objptr_t& object);
    void erase(const_iterator pos);

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    Core::Scene& getRawScene();
    const Core::Scene& getRawScene() const;

private:
    containter_t objects;
    Core::Scene rawScene;
};

#endif // ARCH_SCENE_HPP
