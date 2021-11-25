#include <stdexcept>
#include "RenderTarget/RenderTarget.hpp"


RenderTarget::RenderTarget(unsigned char* data, int w, int h)
    : data(data), width(w), height(h)
{
    if (!Core::is_valid(*this))
        throw std::runtime_error("bad RenderTarget() args.");
}

RenderTarget::RenderTarget(const Core::RenderTarget &renderTarget)
    : data((unsigned char*)renderTarget.data.load()), width(renderTarget.width), height(renderTarget.height)
{
    if (!Core::is_valid(renderTarget))
        throw std::runtime_error("bad RenderTarget.");
}

RenderTarget::operator Core::RenderTarget() const
{
    return Core::make_render_target(data, width, height);
}
