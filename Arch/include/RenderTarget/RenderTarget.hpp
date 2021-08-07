#ifndef ARCH_RENDERTARGET_HPP
#define ARCH_RENDERTARGET_HPP

#include <cstddef>
#include "Core/RenderTarget/RenderTarget.hpp"

class RenderTarget
{
public:
    RenderTarget(unsigned char* data, size_t w, size_t h);
    RenderTarget(const Core::RenderTarget& renderTarget);

    operator Core::RenderTarget() const;

private:
    unsigned char* data;
    size_t width;
    size_t height;
};

#endif //ARCH_RENDERTARGET_HPP
