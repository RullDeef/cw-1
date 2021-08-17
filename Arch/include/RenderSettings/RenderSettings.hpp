#ifndef RENDERSETTINGS_HPP
#define RENDERSETTINGS_HPP

#include <Core/RenderParams.hpp>


class RenderSettings
{
public:
    void applyTo(Core::RenderParams& params) const;
};

#endif // RENDERSETTINGS_HPP
