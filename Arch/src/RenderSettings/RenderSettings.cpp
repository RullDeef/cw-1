#include <thread>
#include "RenderSettings/RenderSettings.hpp"


RenderSettings::RenderSettings()
    : renderType(RenderType::ColorFilling), lightingType(LightingType::Flat),
    faceCullingType(OcclusionCulling | BackFaceCulling),
    threadsCount(std::thread::hardware_concurrency())
{
}

void RenderSettings::applyTo(Core::RenderParams& params) const
{
    params.renderType = renderType;
    params.sceneLightingModel = lightingType;
    params.faceCullingType = faceCullingType;
}

RenderSettings::RenderType RenderSettings::getRenderType() const
{
    return renderType;
}

RenderSettings::LightingType RenderSettings::getLightingType() const
{
    return lightingType;
}

RenderSettings::FaceCullingType RenderSettings::getFaceCullingType() const
{
    return faceCullingType;
}

unsigned int RenderSettings::getThreadsCount() const
{
    return threadsCount;
}

void RenderSettings::setRenderType(RenderType newRenderType)
{
    renderType = newRenderType;
}

void RenderSettings::setLightingType(LightingType newLightingType)
{
    lightingType = newLightingType;
}

void RenderSettings::setFaceCullingType(FaceCullingType newFaceCullingType)
{
    faceCullingType = newFaceCullingType;
}

void RenderSettings::setThreadsCount(unsigned int newThreadsCount)
{
    threadsCount = newThreadsCount;
}
