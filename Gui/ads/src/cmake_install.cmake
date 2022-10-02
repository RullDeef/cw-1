# Install script for directory: /home/rulldeef/Projects/cw-1/Gui/ads/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xheadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/linux/FloatingWidgetTitleBar.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/ads_globals.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockAreaTabBar.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockAreaTitleBar.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockAreaTitleBar_p.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockAreaWidget.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockContainerWidget.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockManager.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockOverlay.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockSplitter.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockWidget.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockWidgetTab.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockingStateReader.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockFocusController.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/ElidingLabel.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/FloatingDockContainer.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/FloatingDragPreview.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/IconProvider.h"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/DockComponentsFactory.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensex" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/license" TYPE FILE FILES
    "/home/rulldeef/Projects/cw-1/LICENSE"
    "/home/rulldeef/Projects/cw-1/gnu-lgpl-v2.1.md"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so.3.7.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so.3.7.0")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so.3.7.0"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/rulldeef/Projects/cw-1/x64/lib/libqtadvanceddocking.so.3.7.0")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so.3.7.0" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so.3.7.0")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so.3.7.0")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/rulldeef/Projects/cw-1/x64/lib/libqtadvanceddocking.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libqtadvanceddocking.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qtadvanceddocking/adsTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qtadvanceddocking/adsTargets.cmake"
         "/home/rulldeef/Projects/cw-1/Gui/ads/src/CMakeFiles/Export/lib/cmake/qtadvanceddocking/adsTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qtadvanceddocking/adsTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/qtadvanceddocking/adsTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qtadvanceddocking" TYPE FILE FILES "/home/rulldeef/Projects/cw-1/Gui/ads/src/CMakeFiles/Export/lib/cmake/qtadvanceddocking/adsTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qtadvanceddocking" TYPE FILE FILES "/home/rulldeef/Projects/cw-1/Gui/ads/src/CMakeFiles/Export/lib/cmake/qtadvanceddocking/adsTargets-noconfig.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/qtadvanceddocking" TYPE FILE FILES
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/qtadvanceddockingConfig.cmake"
    "/home/rulldeef/Projects/cw-1/Gui/ads/src/qtadvanceddockingConfigVersion.cmake"
    )
endif()

