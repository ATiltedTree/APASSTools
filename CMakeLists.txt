cmake_minimum_required(VERSION 3.5)

project(APASSTools LANGUAGES CXX VERSION 1.0.0 HOMEPAGE_URL https://github.com/ATiltedTree/APASSTools)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Config
######################################################################
# Default install path
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "..." FORCE)
endif()

# Static Build option
option(STATIC "Use static Qt5 libraries" OFF)

# Qt Config
if(STATIC)
  set(QT_PREFIX StaticQt5)
else()
  set(QT_PREFIX Qt5)
endif()

set(QT5_PKGS Core Widgets Gui Svg Network)
set(LINKER_FLAGS "")

# Linking
if(STATIC)
  list(APPEND LINKER_FLAGS -static -static-libstdc++ -static-libgcc)
endif()

if(WIN32)
  list(APPEND LINKER_FLAGS -mwindows)
elseif(UNIX)
  list(APPEND LINKER_FLAGS -Wl,-z,relro,-z,now)
endif()

# Better include
include_directories("src")

# TDF Template
set(TDF_TEMPLATE "file %1\\n\
title %2\\n\
RA H  1 9\\n\
units0 -2   # RA 'hours' are really decimal degrees\\n\
de d  10 10\\n\
text 50 4\\n\
~r  1  19  Data from APASS photometry: \\\\n\\n\
~c  1  19 Photometry (APASS):\\\\n\\n\
~r  1  20 \\\\n\\n\
~c 23   6 V-magnitude: %s\\\\n\\n\
~r 23   6  ^V-magnitude^: %s\\\\n\\n\
~r 29   5  ^Error in V^: %s\\\\n\\n\
~c 45   5 B-V: %s\\\\n\\n\
~r 34   6  ^B-magnitude^: %s\\\\n\\n\
~r 40   5  ^Error in B^: %s\\\\n\\n\
~r 20   3  ^number of measurements^: %s\\\\n\\n\
~r  1  20 \\\\n\\n\
~r  1  20  ^ICQ reference key^: AQ.\\\\n\\n\
~r  1  20 \\\\n\\n\
epoch 2000\\n\
field 0.00 21.00\\n\
shown 5\\n\
type 6\\n\
end\\n\
")

# Make config file
configure_file(src/config.h.in config.h @ONLY)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
######################################################################

# Libs
######################################################################
set(LIBS "")

# Custom Libs
if(STATIC)
  list(APPEND LIBS
      ${QT_PREFIX}::QWindowsIntegrationPlugin
      ${QT_PREFIX}::QWindowsVistaStylePlugin
      ${QT_PREFIX}::QSvgPlugin
      ${QT_PREFIX}::QICOPlugin
      ${QT_PREFIX}::QGifPlugin
      ${QT_PREFIX}::QJpegPlugin)
endif(STATIC)

# Qt Libs
foreach(pkg ${QT5_PKGS})
    find_package(${QT_PREFIX} COMPONENTS ${pkg} REQUIRED)
    list(APPEND LIBS ${QT_PREFIX}::${pkg})
endforeach()
######################################################################

# Sources
######################################################################
add_executable(APASSTools)

set(SOURCES
  main.cpp
  ui/CSVDialog/CSVDialog
  ui/CSVDialog/CSVDialog.ui
  ui/APASSTools/APASSTools
  ui/APASSTools/APASSTools.ui
  ui/WebDialog/WebDialog
  ui/WebDialog/WebDialog.ui
  ui/AboutDialog/AboutDialog
  ui/AboutDialog/AboutDialog.ui
  ui/SettingsDialog/SettingsDialog
  ui/SettingsDialog/SettingsDialog.ui
  common/Settings
  common/APASS
  common/Comet
  common/CSVObject
  common/PRN
  common/TDF
  assets/assets.qrc)

foreach(source ${SOURCES})
  string(PREPEND source "src/")
  target_sources(APASSTools PRIVATE ${source})
endforeach()

if(WIN32)
  target_sources(APASSTools PRIVATE src/assets/assets.rc)
endif(WIN32)

target_link_libraries(APASSTools PRIVATE ${LINKER_FLAGS} ${LIBS})

if(STATIC)
  set_target_properties(APASSTools PROPERTIES
    LINK_SEARCH_START_STATIC OFF
    LINK_SEARCH_END_STATIC ON
  )
endif()
######################################################################

# Installing
######################################################################
install(TARGETS APASSTools)
install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION share/doc/APASSTools)
install(FILES ${CMAKE_SOURCE_DIR}/APASSTools.desktop DESTINATION share/applications)
install(FILES ${CMAKE_SOURCE_DIR}/src/assets/icons/logo.svg DESTINATION share/icons/hicolor/scalable/apps RENAME apasstools.svg)
######################################################################

# Packaging
######################################################################
if(WIN32)
  list(APPEND CPACK_GENERATOR "NSIS64")

  set(CPACK_SOURCE_GENERATOR "ZIP")

  set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CMAKE_PROJECT_NAME})
  set(CPACK_NSIS_MUI_ICON ${CMAKE_SOURCE_DIR}/src/assets/icons/logo.ico)
  set(CPACK_NSIS_INSTALLED_ICON_NAME ${CMAKE_BINARY_DIR}/APASSTools.exe)
  set(CPACK_NSIS_PACKAGE_NAME ${CMAKE_PROJECT_NAME})
  set(CPACK_NSIS_DISPLAY_NAME ${CMAKE_PROJECT_NAME})
  set(CPACK_NSIS_MENU_LINKS "bin/APASSTools.exe" ${CMAKE_PROJECT_NAME})
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
elseif(UNIX)
  list(APPEND CPACK_GENERATOR "DEB")
  list(APPEND CPACK_GENERATOR "RPM")

  set(CPACK_SOURCE_GENERATOR "TGZ")

  set(CPACK_DEBIAN_PACKAGE_MAINTAINER "ATiltedTree")
  list(APPEND CPACK_DEBIAN_PACKAGE_DEPENDS qt5-default)
elseif(DARWIN)

endif()

set(CPACK_PACKAGE_VENDOR "ATiltedTree")
set(CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_SOURCE_DIR}/README.md)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)

include(CPack)
######################################################################
