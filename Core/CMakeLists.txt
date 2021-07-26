cmake_minimum_required(VERSION 3.19)
project(Core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

include_directories(include)

add_library(Core STATIC
        src/Core.cpp
        src/FancyRenderer.cpp
        src/FastRender.cpp
        src/Rasterizers/LineRenderer.cpp
        src/Scene/Scene.cpp
        src/Objects/Camera.cpp
        src/Objects/Mesh.cpp
        src/RenderTarget/RenderTarget.cpp
        src/common/math/Ray.cpp)
