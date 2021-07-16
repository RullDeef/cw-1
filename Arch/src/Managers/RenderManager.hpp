#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "RenderTarget.hpp"


class RenderManager
{
public:
    virtual void renderScene(Core::RenderTarget& renderTarget);
};

#endif // RENDERMANAGER_HPP
