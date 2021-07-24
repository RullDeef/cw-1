#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "RenderTarget.hpp"
#include "IManager.hpp"
#include "Camera.hpp"
#include "Scene.hpp"


class RenderManager : public IManager
{
public:
    explicit RenderManager(IManagerFactory& factory);

    virtual void renderScene(Core::RenderTarget& renderTarget);

protected:
    Core::Scene requireScene();
    Core::Camera requireCamera(const Core::Rect &viewport);
};

#endif // RENDERMANAGER_HPP
