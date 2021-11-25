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


RenderTarget Core::make_render_target(unsigned char *data, int width, int height)
{
    RenderTarget res{};

    // TODO: make more params like stride, offset and etc.
    res.data = (Core::Pixel*)data;
    res.width = width;
    res.height = height;
    res.writeLock = false;

    return res;
}

bool Core::is_valid(const RenderTarget& renderTarget)
{
    return renderTarget.data != nullptr && renderTarget.width > 0 && renderTarget.height > 0;
}

RectI Core::get_viewport(const RenderTarget& renderTarget)
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
