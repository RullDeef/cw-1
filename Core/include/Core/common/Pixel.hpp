#ifndef PIXEL_HPP
#define PIXEL_HPP


namespace Core
{
    struct Pixel
    {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
        unsigned char alpha;
    };

    namespace Color
    {
        const Pixel black   = {   0u,   0u,   0u, 255u };
        const Pixel white   = { 255u, 255u, 255u, 255u };
        const Pixel red     = {   0u,   0u, 255u, 255u };
        const Pixel green   = {   0u, 255u,   0u, 255u };
        const Pixel blue    = { 255u,   0u,   0u, 255u };
        const Pixel magenta = { 255u,   0u, 255u, 255u };
    }
}

#endif // PIXEL_HPP
