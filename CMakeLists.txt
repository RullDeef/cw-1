cmake_minimum_required(VERSION 3.19)
project(cw_1)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH Qt5)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)

# Core.lib <- Arch.lib <- Gui.exe

include_directories(Core/src)
include_directories(Core/src/common)
include_directories(Core/src/common/containers)
include_directories(Core/src/common/math)
include_directories(Core/src/Objects)
include_directories(Core/src/Rasterizers)
include_directories(Core/src/RenderTarget)
include_directories(Core/src/Scene)

add_library(Core STATIC
        Core/src/common/containers/list_t.hpp
        Core/src/common/containers/vect_t.hpp
        Core/src/common/math/Mat.hpp
        Core/src/common/math/MatImp.hpp
        Core/src/common/math/Plane.hpp
        Core/src/common/math/Ray.hpp
        Core/src/common/math/Rect.hpp
        Core/src/common/math/RectImp.hpp
        Core/src/common/math/Vec.hpp
        Core/src/common/math/VecImp.hpp
        Core/src/common/ext_math.cpp
        Core/src/common/ext_math.hpp
        Core/src/common/Pixel.hpp
        Core/src/common/StatusCodes.hpp
        Core/src/Objects/Camera.cpp
        Core/src/Objects/Camera.hpp
        Core/src/Objects/Mesh.cpp
        Core/src/Objects/Mesh.hpp
        Core/src/Rasterizers/LineRenderer.cpp
        Core/src/Rasterizers/LineRenderer.hpp
        Core/src/RenderTarget/RenderTarget.cpp
        Core/src/RenderTarget/RenderTarget.hpp
        Core/src/Scene/Scene.hpp
        Core/src/Core.cpp
        Core/src/Core.hpp
        Core/src/FancyRenderer.cpp
        Core/src/FancyRenderer.hpp
        Core/src/FastRender.cpp
        Core/src/FastRender.hpp Arch/src/Objects/IObject.cpp Core/src/Scene/Scene.cpp Core/src/common/math/Ray.cpp Core/src/common/math/PlaneImp.hpp)

include_directories(Arch/src)
include_directories(Arch/src/Loaders)
include_directories(Arch/src/Loaders/ObjLoader)
include_directories(Arch/src/Managers)
include_directories(Arch/src/Objects)
include_directories(Arch/src/Scene)
include_directories(Arch/src/Visitors)

include_directories(Gui/src)
include_directories(Gui/src/Frames)
include_directories(Gui/src/Frames/HierarchyFrame)
include_directories(Gui/src/Frames/ViewportFrame)

add_executable(cw_1
        Arch/src/Loaders/ObjLoader/ObjLoader.cpp
        Arch/src/Loaders/ObjLoader/ObjLoader.hpp
        Arch/src/Loaders/ILoader.hpp
        Arch/src/Managers/RenderManager.cpp
        Arch/src/Managers/RenderManager.hpp
        Arch/src/Objects/IObject.hpp
        Arch/src/Objects/ObjectAdapter.hpp
        Arch/src/Objects/ObjectAdapterImp.hpp
        Arch/src/Scene/Scene.cpp
        Arch/src/Scene/Scene.hpp
        Arch/src/Visitors/IObjectVisitor.hpp
        Arch/src/Arch.cpp
        Arch/src/Arch.hpp

        Gui/src/Frames/HierarchyFrame/HierarchyFrame.cpp
        Gui/src/Frames/HierarchyFrame/HierarchyFrame.hpp
        Gui/src/Frames/ViewportFrame/ViewportFrame.cpp
        Gui/src/Frames/ViewportFrame/ViewportFrame.hpp
        Gui/src/Frames/IFrame.cpp
        Gui/src/Frames/IFrame.hpp
        Gui/src/main.cpp
        Gui/src/MainWindow.cpp
        Gui/src/MainWindow.hpp Arch/src/Objects/IObject.cpp
        Arch/src/Managers/LoadManager.cpp
        Arch/src/Managers/LoadManager.hpp
        Arch/src/Managers/SceneManager.cpp
        Arch/src/Managers/SceneManager.hpp
        Arch/src/Managers/IManagerFactory.cpp
        Arch/src/Managers/IManagerFactory.hpp
        Arch/src/Managers/IManager.cpp
        Arch/src/Managers/IManager.hpp
        Gui/src/Managers/QtLoadManager.cpp
        Gui/src/Managers/QtLoadManager.hpp
        Gui/src/Managers/QtManagerFactory.cpp
        Gui/src/Managers/QtManagerFactory.hpp
        Arch/src/Objects/Adapters/MeshAdapter.cpp
        Arch/src/Objects/Adapters/MeshAdapter.hpp Arch/src/Managers/CameraManager.cpp Arch/src/Managers/CameraManager.hpp)

target_link_libraries(cw_1 Core Qt5::Core Qt5::Widgets)
