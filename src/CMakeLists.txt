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

configure_file(config.hpp.in config.hpp @ONLY)

target_link_libraries(apasstools PUBLIC Qt5::Widgets Qt5::Svg Qt5::Network)

if(WIN32)
  target_sources(apasstools PRIVATE assets/apasstools.rc)
endif()

if(APPLE)
  set_target_properties(
    apasstools
    PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME APASSTools
               OUTPUT_NAME APASSTools
               MACOSX_BUNDLE_GUI_IDENTIFIER de.atiltedtree.apasstools
               MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
               MACOSX_BUNDLE_ICON_FILE APASSTools.icns
  )

  find_package(ImageMagick REQUIRED COMPONENTS convert)

  set(ICONS "")
  set(ICON_SIZES 16 32 128 256 512)
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset"
    COMMAND "${CMAKE_COMMAND}" -E make_directory
            "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset"
  )
  foreach(ICON_SIZE ${ICON_SIZES})
    add_custom_command(
      DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset"
      OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset/icon_${ICON_SIZE}x${ICON_SIZE}.png"
      COMMAND
        "${ImageMagick_convert_EXECUTABLE}" -background none -resize
        ${ICON_SIZE}x${ICON_SIZE} "${CMAKE_SOURCE_DIR}/data/apasstools.svg"
        "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset/icon_${ICON_SIZE}x${ICON_SIZE}.png"
    )
    math(EXPR DOUBLE_SIZE "${ICON_SIZE} * 2")
    add_custom_command(
      DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset"
      OUTPUT
        "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
      COMMAND
        "${ImageMagick_convert_EXECUTABLE}" -background none -resize
        ${DOUBLE_SIZE}x${DOUBLE_SIZE} "${CMAKE_SOURCE_DIR}/data/apasstools.svg"
        "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
    )
    list(
      APPEND
      ICONS
      "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset/icon_${ICON_SIZE}x${ICON_SIZE}.png"
      "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
    )
  endforeach()
  find_program(ICONUTIL iconutil)
  add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/APASSTools.icns"
    DEPENDS ${ICONS}
    COMMAND
      "${ICONUTIL}" --convert icns "${CMAKE_CURRENT_BINARY_DIR}/Icon.iconset"
      --output "${CMAKE_CURRENT_BINARY_DIR}/APASSTools.icns"
  )
  target_sources(
    apasstools PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/APASSTools.icns"
  )
  set_source_files_properties(
    "${CMAKE_CURRENT_BINARY_DIR}/APASSTools.icns"
    PROPERTIES MACOSX_PACKAGE_LOCATION Resources
  )

endif(APPLE)

install(
  TARGETS apasstools
  BUNDLE DESTINATION . COMPONENT Runtime
  RUNTIME DESTINATION bin COMPONENT Runtime
)

if(WIN32)
  # Delegate to Qt's official deployment binary on Windows to copy over the
  # necessary Qt-specific libraries, etc.
  get_target_property(MOC_EXECUTABLE_LOCATION Qt5::moc IMPORTED_LOCATION)
  get_filename_component(
    QT_BINARY_DIRECTORY "${MOC_EXECUTABLE_LOCATION}" DIRECTORY
  )
  find_program(WINDEPLOYQT windeployqt HINTS "${QT_BINARY_DIRECTORY}")

  set(WINDEPLOYQT_ARGS
      "--no-translations
      --no-compiler-runtime
      --no-opengl-sw
      --no-system-d3d-compiler
      --no-angle
      $<IF:$<CONFIG:Debug>,--debug,--release>
      \"\${CMAKE_INSTALL_PREFIX}/bin/apasstools.exe\""
  )

  install(
    CODE "
    execute_process(
      COMMAND \"${WINDEPLOYQT}\" ${WINDEPLOYQT_ARGS}
    )"
  )
  set(CMAKE_INSTALL_UCRT_LIBRARIES ON)
  set(CMAKE_INSTALL_DEBUG_LIBRARIES $<CONFIG:Debug>)
  include(InstallRequiredSystemLibraries)
elseif(APPLE)
  # Delegate to Qt's official deployment binary on Mac to copy over the
  # necessary Qt-specific libraries, etc.
  get_target_property(MOC_EXECUTABLE_LOCATION Qt5::moc IMPORTED_LOCATION)
  get_filename_component(
    QT_BINARY_DIRECTORY "${MOC_EXECUTABLE_LOCATION}" DIRECTORY
  )
  find_program(MACDEPLOYQT macdeployqt HINTS "${QT_BINARY_DIRECTORY}")
  install(
    CODE "
    execute_process(
      COMMAND \"${MACDEPLOYQT}\" \"\${CMAKE_INSTALL_PREFIX}/apasstools.app\"
    )"
  )
endif()
