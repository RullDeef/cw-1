#include "RenderTarget/RenderTarget.hpp"

RenderTarget::RenderTarget(unsigned char* data, size_t w, size_t h)
    : data(data), width(w), height(h)
{
}

RenderTarget::RenderTarget(const Core::RenderTarget &renderTarget)
    : data((unsigned char*)renderTarget.data.load()), width(renderTarget.width), height(renderTarget.height)
{
}

RenderTarget::operator Core::RenderTarget() const
{
    return Core::make_render_target(data, width, height);
}
