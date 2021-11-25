#ifndef ARCH_RENDERTARGET_HPP
#define ARCH_RENDERTARGET_HPP

#include <cstddef>
#include "Core/RenderTarget/RenderTarget.hpp"

class RenderTarget
{
public:
    RenderTarget(unsigned char* data, int w, int h);
    RenderTarget(const Core::RenderTarget& renderTarget);

    operator Core::RenderTarget() const;

private:
    unsigned char* data;
    int width;
    int height;
};

#endif //ARCH_RENDERTARGET_HPP
