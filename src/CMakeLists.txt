find_package(Qt5 REQUIRED COMPONENTS Widgets Svg Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(
  apasstools WIN32 MACOSX_BUNDLE
  main.cpp
  ui/CSVDialog/CSVDialog.cpp
  ui/CSVDialog/CSVDialog.hpp
  ui/APASSTools/APASSTools.cpp
  ui/APASSTools/APASSTools.hpp
  ui/WebDialog/WebDialog.cpp
  ui/WebDialog/WebDialog.hpp
  ui/AboutDialog/AboutDialog.cpp
  ui/AboutDialog/AboutDialog.hpp
  ui/SettingsDialog/SettingsDialog.cpp
  ui/SettingsDialog/SettingsDialog.hpp
  common/Settings.cpp
  common/Settings.hpp
  common/APASS.cpp
  common/APASS.hpp
  common/Comet.cpp
  common/Comet.hpp
  common/CSVObject.cpp
  common/CSVObject.hpp
  common/PRNFile.cpp
  common/PRNFile.hpp
  common/TDFFile.cpp
  common/TDFFile.hpp
  common/Icon.cpp
  common/Icon.hpp
  assets/apasstools.qrc
)

configure_file(config.hpp.in config.hpp)

target_link_libraries(apasstools PUBLIC Qt5::Widgets Qt5::Svg Qt5::Network)

include(BuildIcon)

if(WIN32)
  set(ICON_SIZES 16 32 48 256)
  build_icon(
    apasstools "${CMAKE_SOURCE_DIR}/data/apasstools.svg" "${ICON_SIZES}"
  )

  configure_file(assets/apasstools.rc.in assets/apasstools.rc)
  target_sources(
    apasstools PRIVATE "${ICON}"
                       "${CMAKE_CURRENT_BINARY_DIR}/assets/apasstools.rc"
  )

elseif(APPLE)
  set(ICON_SIZES 16 32 128 256 512)
  build_icon(
    apasstools "${CMAKE_SOURCE_DIR}/data/apasstools.svg" "${ICON_SIZES}"
  )

  target_sources(apasstools PRIVATE "${ICON}")
  set_source_files_properties(
    "${ICON}" PROPERTIES MACOSX_PACKAGE_LOCATION Resources
  )

  get_filename_component(ICON_NAME "${ICON}" NAME)

  set_target_properties(
    apasstools
    PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME APASSTools
               OUTPUT_NAME APASSTools
               MACOSX_BUNDLE_GUI_IDENTIFIER de.atiltedtree.apasstools
               MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
               MACOSX_BUNDLE_ICON_FILE ${ICON_NAME}
  )
endif()

install(
  TARGETS apasstools
  BUNDLE DESTINATION . COMPONENT Runtime
  RUNTIME DESTINATION bin COMPONENT Runtime
)

include(DeployQt)

if(WIN32)
  deploy_qt(
    "--no-translations
    --no-compiler-runtime
    --no-opengl-sw
    --no-system-d3d-compiler
    --no-angle
    $<IF:$<CONFIG:Debug>,--debug,--release>
    \\\${CMAKE_INSTALL_PREFIX}/bin/apasstools.exe"
  )
elseif(APPLE)
  deploy_qt("\\\${CMAKE_INSTALL_PREFIX}/apasstools.app")
endif()
