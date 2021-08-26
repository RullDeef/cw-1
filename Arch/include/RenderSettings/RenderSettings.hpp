#ifndef RENDERSETTINGS_HPP
#define RENDERSETTINGS_HPP

#include <Core/RenderParams.hpp>


class RenderSettings
{
public:
    using RenderType = Core::RenderType;
    using LightingType = Core::LightingModelType;
    using FaceCullingType = Core::FaceCullingType;

    static const FaceCullingType NoCulling = 0;
    static const FaceCullingType OcclusionCulling = Core::OcclusionCulling;
    static const FaceCullingType BackFaceCulling = Core::BackfaceCulling;

    RenderSettings();

    void applyTo(Core::RenderParams& params) const;

    [[nodiscard]] RenderType getRenderType() const;
    [[nodiscard]] LightingType getLightingType() const;
    [[nodiscard]] FaceCullingType getFaceCullingType() const;

    [[nodiscard]] unsigned int getThreadsCount() const;

    void setRenderType(RenderType newRenderType);
    void setLightingType(LightingType newLightingType);
    void setFaceCullingType(FaceCullingType newFaceCullingType);

    void setThreadsCount(unsigned int newThreadsCount);

private:
    RenderType renderType;
    LightingType lightingType;
    FaceCullingType faceCullingType;

    unsigned int threadsCount;
};

#endif // RENDERSETTINGS_HPP
