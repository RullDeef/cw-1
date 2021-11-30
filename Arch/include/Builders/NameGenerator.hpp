//
// Created by rulldeef on 11/30/21.
//

#ifndef NAMEGENERATOR_HPP
#define NAMEGENERATOR_HPP

#include <string>


class NameGenerator
{
public:
    static std::string indexise(const std::string& name, size_t index);

    static std::string globalName();

private:
    static size_t globalCounter;
};

#endif //NAMEGENERATOR_HPP
