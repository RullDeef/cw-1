#include "Core/RenderTarget/RenderTarget.hpp"

using namespace Core;


RenderTarget::RenderTarget(const RenderTarget& src)
    : data(src.data.load()), width(src.width), height(src.height), writeLock(static_cast<bool>(src.writeLock))
{
}

RenderTarget& RenderTarget::operator=(const RenderTarget& src)
{
    data = src.data.load();
    width = src.width;
    height = src.height;
    writeLock = src.writeLock.load();

    return *this;
}


RenderTarget Core::make_render_target(unsigned char *data, size_t w, size_t h)
{
    RenderTarget res{};

    res.data = (Core::Pixel*)data;
    res.width = w;
    res.height = h;
    res.writeLock = false;

    return res;
}

Rect Core::get_viewport(const RenderTarget& renderTarget)
{
    return make_rect(renderTarget.width, renderTarget.height);
}

void Core::setPixel(RenderTarget& renderTarget, size_t row, size_t col, Pixel pixel)
{
    if (row >= renderTarget.height || col >= renderTarget.width)
        return; /// TODO: log error

    Pixel* data = nullptr;
    do { data = renderTarget.data.exchange(nullptr); } while (data == nullptr);
    data[row * renderTarget.width + col] = pixel;
    renderTarget.data.exchange(data);
}

void Core::fill(RenderTarget& renderTarget, Pixel pixel)
{
    for (size_t row = 0; row < renderTarget.height; row++)
        for (size_t col = 0; col < renderTarget.width; col++)
            setPixel(renderTarget, row, col, pixel);
}

void Core::lock(RenderTarget& renderTarget)
{
    bool locked;
    do { locked = false; }
    while (renderTarget.writeLock.compare_exchange_strong(locked, true, std::memory_order_acquire));
}

void Core::unlock(RenderTarget& renderTarget)
{
    renderTarget.writeLock.store(false, std::memory_order_release);
}
