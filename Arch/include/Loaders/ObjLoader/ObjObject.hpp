#ifndef OBJOBJECT_HPP
#define OBJOBJECT_HPP

#include <utility>
#include "Loaders/ObjLoader/ObjFace.hpp"


class ObjObject
{
public:
    using const_iterator = std::vector<ObjFace>::const_iterator;

    ObjObject() = default;
    explicit ObjObject(std::string  name) : name(std::move(name)) {}

    bool empty() const noexcept { return faces.empty(); }

    const std::string& getName() const { return name; }
    const std::string& getMaterialName() const { return materialName; }

    void setName(const std::string& newName) { name = newName; }
    void setMaterialName(const std::string& newMaterial) { materialName = newMaterial; }

    void addFace(const ObjFace& face) { faces.push_back(face); }

    const_iterator begin() const { return faces.begin(); }
    const_iterator end() const { return faces.end(); }

private:
    std::string name = "";
    std::string materialName = "";
    std::vector<ObjFace> faces;
};

#endif // OBJOBJECT_HPP
