#include <cstdlib>
#include "Core/RenderTarget/ZBuffer.hpp"

using namespace Core;


ZBuffer Core::make_zbuffer(size_t width, size_t height)
{
    ZBuffer buffer{};

    buffer.width = width;
    buffer.height = height;
    buffer.data = (double *) std::calloc(width * height, sizeof(double));

    return buffer;
}

void Core::destroy(ZBuffer &buffer)
{
    if (buffer.data != nullptr)
    {
        std::free(buffer.data);
        buffer.data = nullptr;
    }
    buffer.width = 0;
    buffer.height = 0;
}

void Core::fill(ZBuffer& buffer, double value)
{
    for (size_t row = 0; row < buffer.height; row++)
        for (size_t col = 0; col < buffer.width; col++)
            buffer.data[row * buffer.width + col] = value;
}

double Core::getZ(const ZBuffer &buffer, size_t row, size_t col)
{
    if (row < buffer.height && col < buffer.width)
    {
        size_t index = row * buffer.width + col;
        return buffer.data[index];
    }

    return 0.0;
}

void Core::setZ(ZBuffer &buffer, size_t row, size_t col, double value)
{
    if (row < buffer.height && col < buffer.width)
    {
        size_t index = row * buffer.width + col;
        buffer.data[index] = value;
    }
}

void Core::updatePixel(RenderTarget& renderTarget, ZBuffer& buffer, size_t row, size_t col, double z, Pixel color)
{
    double zPrev = getZ(buffer, row, col);
    if (z < zPrev)
    {
        setPixel(renderTarget, row, col, color);
        setZ(buffer, row, col, z);
    }
}
