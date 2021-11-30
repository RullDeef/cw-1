//
// Created by rulldeef on 11/30/21.
//

#include "Builders/NameGenerator.hpp"

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
