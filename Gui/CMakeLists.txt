cmake_minimum_required(VERSION 3.19)
project(Gui)

set(CMAKE_CXX_STANDARD 17)

if(DEFINED ENV{DEBUG})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH Qt5)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_subdirectory(ads)
include_directories(ads/src)

include_directories(../Core/include)
include_directories(../Arch/include)
include_directories(src)

add_executable(Gui
        src/main.cpp
        src/MainWindow.cpp
        src/Frames/HierarchyFrame/HierarchyFrame.cpp
        src/Frames/ViewportFrame/ViewportFrame.cpp
        src/Frames/ViewportFrame/FreeFlyDispatcher/FreeFlyDispatcher.cpp
        src/Frames/IFrame.cpp
        src/Managers/QtLoadManager.cpp
        src/Managers/QtManagerFactory.cpp
        src/ItemModels/ObjectModel.cpp
        src/Frames/HierarchyFrame/ObjectView/ObjectView.cpp
        src/Frames/HierarchyFrame/CheckBoxDelegate/CheckBoxDelegate.cpp
        src/Frames/InspectorFrame/InspectorFrame.cpp
        src/Frames/InspectorFrame/InspectorWidget/InspectorWidget.cpp
        src/Frames/InspectorFrame/InspectorWidget/InspectorWidget.ui src/Frames/SettingsFrame/SettingsFrame.cpp src/Frames/SettingsFrame/SettingsFrame.hpp src/Frames/SettingsFrame/SettingsWidget/SettingsWidget.cpp src/Frames/SettingsFrame/SettingsWidget/SettingsWidget.hpp src/Frames/SettingsFrame/SettingsWidget/SettingsWidget.ui src/Managers/QtSceneManager.cpp src/Managers/QtSceneManager.hpp src/Managers/QtCameraManager.cpp src/Managers/QtCameraManager.hpp src/Managers/QtRenderManager.cpp src/Managers/QtRenderManager.hpp src/Managers/QtSelectionManager.cpp src/Managers/QtSelectionManager.hpp src/Widgets/RenderWidget.cpp src/Widgets/RenderWidget.hpp)

target_link_libraries(Gui PRIVATE qtadvanceddocking PUBLIC Arch Core Qt5::Core Qt5::Widgets pthread)
