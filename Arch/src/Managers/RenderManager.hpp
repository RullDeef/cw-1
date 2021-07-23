#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "RenderTarget.hpp"
#include "IManager.hpp"


class RenderManager : public IManager
{
public:
    explicit RenderManager(IManagerFactory& factory);

    virtual void renderScene(Core::RenderTarget& renderTarget);
};

#endif // RENDERMANAGER_HPP
