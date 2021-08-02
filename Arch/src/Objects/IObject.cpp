#include "Objects/IObject.hpp"

IObject::IObject(size_t id)
    : id(id)
{
}

size_t IObject::getId() const noexcept
{
    return id;
}

const std::string &IObject::getName() const noexcept
{
    return name;
}

void IObject::setName(const std::string &newName)
{
    name = newName;
}

bool IObject::isSelected() const noexcept
{
    return selected;
}

void IObject::setSelected(bool newSelected) noexcept
{
    selected = newSelected;
}
