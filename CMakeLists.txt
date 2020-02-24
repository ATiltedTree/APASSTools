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
if(WIN32)
  option(STATIC "Use static Qt5 libraries" ON)
endif(WIN32)

# Qt Config
if(STATIC)
  set(QT_PREFIX StaticQt5)
  set(QT5_PKGS Core Widgets Gui Svg Network)
else()
  set(QT_PREFIX Qt5)
  set(QT5_PKGS Core Widgets Gui Svg Network)
endif()

# Linking
if(STATIC)
  set(LINKER_FLAGS -static -static-libstdc++ -static-libgcc -mwindows)
else()
    set(LINKER_FLAGS -Wl,-z,relro,-z,now)
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
# Custom Libs
if(WIN32)
  set(LIBS
          ${QT_PREFIX}::QWindowsIntegrationPlugin
          ${QT_PREFIX}::QWindowsVistaStylePlugin
          ${QT_PREFIX}::QSvgPlugin
          ${QT_PREFIX}::QICOPlugin
          ${QT_PREFIX}::QGifPlugin
          ${QT_PREFIX}::QJpegPlugin)
else()
  set(LIBS "")
endif(WIN32)

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
  assets/icons/icons.qrc)

foreach(source ${SOURCES})
  string(PREPEND source "src/")
  target_sources(APASSTools PRIVATE ${source})
endforeach()

target_link_libraries(APASSTools PRIVATE ${LINKER_FLAGS} ${LIBS})

if(STATIC)
  set_target_properties(APASSTools PROPERTIES
    LINK_SEARCH_START_STATIC ON
    LINK_SEARCH_END_STATIC ON
  )
endif()
######################################################################
