cmake_minimum_required(VERSION 3.19)
project(Arch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if (DEFINED ENV{DEBUG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(../Core/include)
include_directories(include)

add_library(Arch STATIC
        src/Managers/SettingsManager.cpp
        src/Managers/SelectionManager.cpp
        src/Managers/LoadManager.cpp
        src/Managers/RenderManager.cpp
        src/Managers/CameraManager.cpp
        src/Managers/SceneManager.cpp
        src/Managers/IManagerFactory.cpp
        src/Managers/IManager.cpp
        src/Loaders/ObjLoader/ObjLoader.cpp
        src/Loaders/ObjLoader/ObjFace.cpp
        src/Builders/CameraBuilders/DefaultCameraBuilder.cpp
        src/Builders/LightBuilders/AmbientLightBuilder.cpp
        src/Builders/EmptySceneBuilder.cpp
        src/Builders/DefaultIDGenerator.cpp
        src/Scene/Scene.cpp
        src/Objects/Adapters/MeshAdapter.cpp
        src/Objects/Adapters/CameraAdapter.cpp
        src/Objects/Adapters/LightAdapter.cpp
        src/Objects/Mesh.cpp
        src/Objects/Material.cpp
        src/Objects/Camera.cpp
        src/Objects/Light.cpp
        src/Objects/IObject.cpp
        src/Visitors/Transformer.cpp
        src/RenderSettings/RenderSettings.cpp
        src/RenderTarget/RenderTarget.cpp
        src/Math/Ray.cpp
        src/Math/Rect.cpp
        src/Math/Matrix.cpp
        src/Math/Vector.cpp src/Threading/ThreadPool.cpp src/Managers/InfoManager.cpp)

link_libraries(Arch Core)
