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

    [[nodiscard]] bool isVisible() const noexcept;
    void setVisible(bool newVisible) noexcept;

    [[nodiscard]] bool isSelected() const noexcept;
    void setSelected(bool newSelected) noexcept;

    [[nodiscard]] Vector getPosition() const noexcept;
    [[nodiscard]] Vector getRotation() const noexcept;
    [[nodiscard]] Vector getScale() const noexcept;

    [[nodiscard]] Matrix getTransform() const;

    void setPosition(const Vector& value);

    /**
     * Rotation always goes in degrees, not radians!
     */
    void setRotation(const Vector& value);
    void setScale(const Vector& value);

    virtual void accept(IObjectVisitor& visitor) = 0;

    virtual bool intersects(double& t, const Ray& ray) = 0;

protected:
    virtual void onNameChange() {}
    virtual void onVisibilityChange() {}
    virtual void onSelectionChange() {}
    virtual void onTransformChange() {}

private:
    const size_t id;
    std::string name;
    bool visible = true;
    bool selected = false;

    Vector position = Vector(0, 0, 0, 1);
    Vector rotation = Vector(0, 0, 0, 0);
    Vector scale = Vector(1, 1, 1, 0);
};

#endif // IOBJECT_HPP
