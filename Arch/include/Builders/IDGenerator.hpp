#ifndef IDGENERATOR_HPP
#define IDGENERATOR_HPP

#include <cstddef>


class IDGenerator
{
public:
    virtual ~IDGenerator() = default;

    virtual size_t generate() = 0;
};

#endif // IDGENERATOR_HPP
