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
        src/Frames/HierarchyFrame/ObjectListItemWidget/ObjectListItemWidget.cpp
        src/Frames/ViewportFrame/ViewportFrame.cpp
        src/Frames/ViewportFrame/FreeFlyDispatcher/FreeFlyDispatcher.cpp
        src/Frames/IFrame.cpp
        src/Managers/QtLoadManager.cpp
        src/Managers/QtManagerFactory.cpp)

target_link_libraries(Gui PRIVATE qtadvanceddocking PUBLIC Arch Core Qt5::Core Qt5::Widgets pthread)
