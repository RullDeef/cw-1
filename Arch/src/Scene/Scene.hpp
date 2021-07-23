#ifndef ARCH_SCENE_HPP
#define ARCH_SCENE_HPP

#include <memory>
#include <list>

class IObject;


class Scene
{
public:
    using objptr_t = std::shared_ptr<IObject>;
    using containter_t = std::list<objptr_t>;
    using iterator = containter_t::iterator;
    using const_iterator = containter_t::const_iterator;

public:
    void insert(const_iterator pos, const objptr_t& object);
    void erase(const_iterator pos);

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

private:
    containter_t objects;
};

#endif // ARCH_SCENE_HPP
