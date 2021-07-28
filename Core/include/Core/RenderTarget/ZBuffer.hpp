#ifndef ZBUFFER_HPP
#define ZBUFFER_HPP

#include <cstddef>
#include "Core/RenderTarget/RenderTarget.hpp"


namespace Core
{
    struct ZBuffer
    {
        double *data;
        size_t width;
        size_t height;
    };

    ZBuffer make_zbuffer(size_t width, size_t height);
    void destroy(ZBuffer& buffer);

    void fill(ZBuffer& buffer, double value);

    double getZ(const ZBuffer& buffer, size_t row, size_t col);
    void setZ(ZBuffer& buffer, size_t row, size_t col, double value);

    void updatePixel(RenderTarget& renderTarget, ZBuffer& buffer, size_t row, size_t col, double z, Pixel color);
}

#endif // ZBUFFER_HPP
