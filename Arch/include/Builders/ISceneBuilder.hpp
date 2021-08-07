#ifndef ISCENEBUILDER_HPP
#define ISCENEBUILDER_HPP

#include <memory>
#include "Scene/Scene.hpp"


class ISceneBuilder
{
public:
    virtual ~ISceneBuilder() = default;

    virtual std::unique_ptr<Scene> build() = 0;
};

#endif // ISCENEBUILDER_HPP
