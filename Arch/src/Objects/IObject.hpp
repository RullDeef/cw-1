#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <string>

class IObjectVisitor;


class IObject
{
public:
    explicit IObject(size_t id);
    virtual ~IObject() = default;

    size_t getId() const noexcept;

    const std::string& getName() const noexcept;
    void setName(const std::string& newName);

    virtual void accept(IObjectVisitor& visitor) = 0;

private:
    const size_t id;
    std::string name;
};

#endif // IOBJECT_HPP
