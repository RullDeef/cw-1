#include "Objects/IObject.hpp"

IObject::IObject(size_t id)
    : id(id), scale(1, 1, 1)
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
    onNameChange();
}

bool IObject::isSelected() const noexcept
{
    return selected;
}

void IObject::setSelected(bool newSelected) noexcept
{
    selected = newSelected;
    onSelectionChange();
}

Vector IObject::getPosition() const noexcept
{
    return position;
}

Vector IObject::getRotation() const noexcept
{
    return rotation * 180.0 / M_PI;
}

Vector IObject::getScale() const noexcept
{
    return scale;
}

Matrix IObject::getTransform() const
{
    return Matrix::trsModel(position, rotation, scale);
}

void IObject::setPosition(const Vector &value)
{
    position = value;
    onTransformChange();
}

void IObject::setRotation(const Vector &value)
{
    rotation = value / 180.0 * M_PI;
    onTransformChange();
}

void IObject::setScale(const Vector &value)
{
    scale = value;
    onTransformChange();
}
