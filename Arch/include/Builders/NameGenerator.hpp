//
// Created by rulldeef on 11/30/21.
//

#ifndef NAMEGENERATOR_HPP
#define NAMEGENERATOR_HPP

#include <string>
#include <Scene/Scene.hpp>


class NameGenerator
{
public:
    static std::string indexise(const std::string& name, size_t index);

    static std::string globalName();

    static std::string uniqueIndexedName(const std::string& baseName, const Scene& scene);

private:
    static size_t globalCounter;
};

#endif //NAMEGENERATOR_HPP
