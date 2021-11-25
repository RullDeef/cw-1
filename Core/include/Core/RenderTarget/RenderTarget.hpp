#ifndef RENDERTARGET_HPP
#define RENDERTARGET_HPP

#include <atomic>
#include <cstddef>
#include "Core/math/Rect.hpp"
#include "Core/common/Pixel.hpp"


namespace Core
{
    struct RenderTarget
    {
        std::atomic<Pixel*> data;
        int width;
        int height;

        std::atomic<bool> writeLock;

        RenderTarget() = default;
        RenderTarget(const RenderTarget& src);

        RenderTarget& operator=(const RenderTarget& src);
    };

    RenderTarget make_render_target(unsigned char* data, int width, int height);
    bool is_valid(const RenderTarget& renderTarget);

    RectI get_viewport(const RenderTarget& renderTarget);

    Pixel getPixel(const RenderTarget& renderTarget, size_t row, size_t col);
    void setPixel(RenderTarget& renderTarget, size_t row, size_t col, Pixel pixel);

    void fill(RenderTarget& renderTarget, Pixel pixel);

    void lock(RenderTarget& renderTarget);
    void unlock(RenderTarget& renderTarget);
}

#endif // RENDERTARGET_HPP
