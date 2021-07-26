cmake_minimum_required(VERSION 3.19)
project(Arch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

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
        src/Objects/IObject.cpp)

link_libraries(Arch Core)
