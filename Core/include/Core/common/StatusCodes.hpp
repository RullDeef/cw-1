#ifndef STATUSCODES_HPP
#define STATUSCODES_HPP

namespace Core
{
    enum class StatusCode
    {
        Success,
        InvalidRenderType,
        InvalidRenderViewport,

        UnsupportedLightingModelType,
    };
}

#endif // STATUSCODES_HPP
