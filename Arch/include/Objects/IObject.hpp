#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <string>
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
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

    [[nodiscard]] const Vector& getPosition() const noexcept;
    [[nodiscard]] const Vector& getRotation() const noexcept;
    [[nodiscard]] const Vector& getScale() const noexcept;

    [[nodiscard]] Matrix getTransform() const;

    void setPosition(const Vector& value);
    void setRotation(const Vector& value);
    void setScale(const Vector& value);

    virtual void accept(IObjectVisitor& visitor) = 0;

    virtual bool intersects(double& t, const Ray& ray) = 0;

protected:
    virtual void onNameChange() {}
    virtual void onSelectionChange() {}
    virtual void onTransformChange() {}

private:
    const size_t id;
    std::string name;
    bool selected = false;

    Vector position;
    Vector rotation;
    Vector scale;
};

#endif // IOBJECT_HPP
