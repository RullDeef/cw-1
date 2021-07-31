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

    const Pixel pBlack   = {   0u,   0u,   0u, 255u };
    const Pixel pWhite   = { 255u, 255u, 255u, 255u };
    const Pixel pRed     = {   0u,   0u, 255u, 255u };
    const Pixel pGreen   = {   0u, 255u,   0u, 255u };
    const Pixel pBlue    = { 255u,   0u,   0u, 255u };
    const Pixel pMagenta = { 255u,   0u, 255u, 255u };
}

#endif // PIXEL_HPP
