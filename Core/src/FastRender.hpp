#ifndef FASTRENDER_HPP
#define FASTRENDER_HPP

#include "StatusCodes.hpp"
#include "RenderTarget.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


namespace Core
{
    StatusCode fastRenderScene(RenderTarget& renderTarget, const Scene& scene, const Camera& camera);
}

#endif // FASTRENDER_HPP
