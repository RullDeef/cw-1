cmake_minimum_required(VERSION 3.19)
project(Arch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(DEFINED ENV{DEBUG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(../Core/include)
include_directories(include)

add_library(Arch STATIC
        src/Arch.cpp
        src/Managers/LoadManager.cpp
        src/Managers/RenderManager.cpp
        src/Managers/CameraManager.cpp
        src/Managers/SceneManager.cpp
        src/Managers/IManagerFactory.cpp
        src/Managers/IManager.cpp
        src/Loaders/ObjLoader/ObjLoader.cpp
        src/Scene/Scene.cpp
        src/Objects/Adapters/MeshAdapter.cpp
        src/Objects/Adapters/CameraAdapter.cpp
        src/Objects/IObject.cpp
        src/Visitors/Transformer.cpp
        src/Managers/ObjectManager.cpp include/Math/Vector.hpp src/Math/Vector.cpp include/Math/Matrix.hpp src/Math/Matrix.cpp include/Math/Ray.hpp include/RenderTarget/RenderTarget.hpp src/Math/Ray.cpp src/RenderTarget/RenderTarget.cpp)

link_libraries(Arch Core)
