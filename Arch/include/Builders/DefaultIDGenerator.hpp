#ifndef DEFAULTIDGENERATOR_HPP
#define DEFAULTIDGENERATOR_HPP

#include "Builders/IDGenerator.hpp"


class DefaultIDGenerator : public IDGenerator
{
public:
    size_t generate() override;
};

#endif // DEFAULTIDGENERATOR_HPP
