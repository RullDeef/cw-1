#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <string>
#include "Math/Ray.hpp"

class IObjectVisitor;


class IObject
{
public:
    explicit IObject(size_t id);
    virtual ~IObject() = default;

    [[nodiscard]] size_t getId() const noexcept;

    [[nodiscard]] const std::string& getName() const noexcept;
    void setName(const std::string& newName);

    [[nodiscard]] bool isSelected() const noexcept;
    void setSelected(bool newSelected) noexcept;

    virtual void accept(IObjectVisitor& visitor) = 0;

    virtual bool intersects(double& t, const Ray& ray) = 0;

protected:
    virtual void onNameChange() {}
    virtual void onSelectionChange() {}

private:
    const size_t id;
    std::string name;
    bool selected = false;
};

#endif // IOBJECT_HPP
