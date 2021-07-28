#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "Core/RenderTarget/RenderTarget.hpp"
#include "Core/Objects/Camera.hpp"
#include "Core/Scene/Scene.hpp"
#include "IManager.hpp"


class RenderManager : public IManager
{
public:
    explicit RenderManager(IManagerFactory& factory);

    virtual void renderSceneFast(Core::RenderTarget& renderTarget);
    virtual void renderSceneFancy(Core::RenderTarget& renderTarget);

protected:
    Core::Scene requireScene();
    Core::Camera requireCamera(const Core::RenderTarget& renderTarget);
    Core::Camera requireCamera(const Core::Rect &viewport);
};

#endif // RENDERMANAGER_HPP
