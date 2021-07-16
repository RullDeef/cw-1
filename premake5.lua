require "premake/qt"
local qt = premake.extensions.qt

workspace "Wargo"
    configurations { "Debug", "Release" }
    architecture "x64"

    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj"

    files { "%{prj.name}/src/**.hpp", "%{prj.name}/src/**.cpp" }

    project "Core"
        kind "StaticLib"
        location "%{prj.name}"
        includedirs { "Core/src", "Core/src/**" }

    project "Arch"
        kind "StaticLib"
        location "%{prj.name}"
        includedirs { "Core/src", "Core/src/**", "Arch/src/**" }
        links { "Core" }

    project "Gui"
        kind "ConsoleApp"
        location "%{prj.name}"

        qt.enable()
        qtmodules { "core", "gui", "widgets" }
        qtprefix "Qt6"

        files { "%{prj.name}/src/**.ui" }
        includedirs { "Core/src", "Core/src/**", "Arch/src/**", "Gui/src/**" }
        links { "Arch" }

        configuration { "Debug" }
            qtsuffix "d"
