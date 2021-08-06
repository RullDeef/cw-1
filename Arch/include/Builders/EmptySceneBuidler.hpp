#ifndef EMPTYSCENEBUIDLER_HPP
#define EMPTYSCENEBUIDLER_HPP

#include "Builders/ISceneBuilder.hpp"


class EmptySceneBuilder : public ISceneBuilder
{
public:
    std::unique_ptr<Scene> build() override;
};

#endif // EMPTYSCENEBUIDLER_HPP
