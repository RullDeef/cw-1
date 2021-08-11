cmake_minimum_required(VERSION 3.19)
project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(DEFINED ENV{DEBUG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(include)

add_library(Core STATIC
        src/Core.cpp
        src/FancyRenderer.cpp
        src/FastRender.cpp
        src/Rasterizers/RenderRegion.cpp
        src/Rasterizers/RectRenderer.cpp
        src/Rasterizers/LineRenderer.cpp
        src/Scene/Scene.cpp
        src/Objects/Camera.cpp
        src/Objects/Mesh.cpp
        src/Objects/Material.cpp
        src/Objects/Face.cpp
        src/Objects/Vertex.cpp
        src/RenderTarget/ZBuffer.cpp
        src/RenderTarget/RenderTarget.cpp
        src/math/Ray.cpp
        src/RenderParams.cpp src/Objects/Light.cpp src/OverlayRenderer.cpp src/Rasterizers/CircleRenderer.cpp)
