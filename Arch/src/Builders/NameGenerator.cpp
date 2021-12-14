//
// Created by rulldeef on 11/30/21.
//

#include "Builders/NameGenerator.hpp"
#include "Objects/IObject.hpp"

size_t NameGenerator::globalCounter = 0;

std::string NameGenerator::indexise(const std::string &name, size_t index)
{
    if (index == 0)
        return name;
    return name + " (" + std::to_string(index) + ")";
}

std::string NameGenerator::globalName()
{
    return indexise("Object", globalCounter++);
}

std::string NameGenerator::uniqueIndexedName(const std::string& baseName, const Scene &scene)
{
    std::string name = baseName;
    size_t index = 0;
    bool nameChanged;

    do
    {
        nameChanged = false;
        for (const auto& obj : scene)
        {
            if (obj->getName() == name)
            {
                name = baseName + " (" + std::to_string(++index) + ")";
                nameChanged = true;
                break;
            }
        }
    }
    while (nameChanged);

    return name;
}
