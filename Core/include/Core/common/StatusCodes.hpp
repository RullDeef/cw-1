#ifndef STATUSCODES_HPP
#define STATUSCODES_HPP

namespace Core
{
    enum class StatusCode
    {
        Success,
        InvalidRenderType,
        InvalidRenderViewport,

        InvalidRect,
        InvalidRenderTarget,

        UnsupportedLightingModelType,
    };
}

#endif // STATUSCODES_HPP
