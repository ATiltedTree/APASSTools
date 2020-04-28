find_package(Qt5 REQUIRED COMPONENTS Widgets Svg Network)

set(CMAKE_AUTOMOC ON)

add_executable(
  APASSTools WIN32
  main.cpp
  ui/CSVDialog/CSVDialog.cpp
  ui/CSVDialog/CSVDialog.h
  ui/APASSTools/APASSTools.cpp
  ui/APASSTools/APASSTools.h
  ui/WebDialog/WebDialog.cpp
  ui/WebDialog/WebDialog.h
  ui/AboutDialog/AboutDialog.cpp
  ui/AboutDialog/AboutDialog.h
  ui/SettingsDialog/SettingsDialog.cpp
  ui/SettingsDialog/SettingsDialog.h
  common/Settings.cpp
  common/Settings.h
  common/APASS.cpp
  common/APASS.h
  common/Comet.cpp
  common/Comet.h
  common/CSVObject.cpp
  common/CSVObject.h
  common/PRNFile.cpp
  common/PRNFile.h
  common/TDFFile.cpp
  common/TDFFile.h
)

configure_file(config.h.in config.h @ONLY)

target_link_libraries(APASSTools PRIVATE Qt5::Widgets Qt5::Svg Qt5::Network)

if(STATIC)
  qt5_import_plugins(APASSTools INCLUDE Qt5::QSvgPlugin)
  target_link_libraries(APASSTools PRIVATE Qt5::QSvgPlugin)
  target_link_libraries(APASSTools PRIVATE -static -static-libstdc++ -static-libgcc)
  set_target_properties(
    APASSTools PROPERTIES LINK_SEARCH_START_STATIC OFF LINK_SEARCH_END_STATIC ON
  )
endif()

if(WIN32)
  target_sources(APASSTools PRIVATE apasstools.rc)

  if(STATIC)
    qt5_import_plugins(
      APASSTools INCLUDE Qt5::QWindowsIntegrationPlugin Qt5::QWindowsVistaStylePlugin
    )
    target_link_libraries(
      APASSTools PRIVATE Qt5::QWindowsIntegrationPlugin Qt5::QWindowsVistaStylePlugin
    )
  else()
    # Delegate to Qt's official deployment binary on Windows to copy over the necessary Qt-specific
    # libraries, etc.
    get_target_property(MOC_EXECUTABLE_LOCATION Qt5::moc IMPORTED_LOCATION)
    get_filename_component(QT_BINARY_DIRECTORY "${MOC_EXECUTABLE_LOCATION}" DIRECTORY)
    find_program(WINDEPLOYQT_EXE windeployqt HINTS "${QT_BINARY_DIRECTORY}")

    set(WINDEPLOYQT_ARGS
        "
        --no-translations
        --no-compiler-runtime
        --no-opengl-sw
        --no-system-d3d-compiler
        --no-angle
        $<IF:$<STREQUAL:${CMAKE_BUILD_TYPE},Release>,--release,--debug>
        $<TARGET_FILE:APASSTools>"
    )

  endif()
endif()

install(TARGETS APASSTools)
if(WIN32)
  install(
    CODE "
  execute_process(
    COMMAND
      \"${CMAKE_COMMAND}\" -E env PATH=\"${QT_BINARY_DIRECTORY}\"
      \"${WINDEPLOYQT_EXE}\"
      ${WINDEPLOYQT_ARGS}
      --dry-run
      --list mapping
    OUTPUT_VARIABLE _output
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  separate_arguments(_files WINDOWS_COMMAND \${_output})
  while(_files)
    list(GET _files 0 _src)
    list(GET _files 1 _dest)
    execute_process(
                COMMAND \"${CMAKE_COMMAND}\" -E
                    copy \${_src} \"\${CMAKE_INSTALL_PREFIX}/bin/\${_dest}\"
            )
    list(REMOVE_AT _files 0 1)
  endwhile()
  "
  )
  set(CMAKE_INSTALL_UCRT_LIBRARIES ON)
  if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_INSTALL_DEBUG_LIBRARIES ON)
  endif()
  include(InstallRequiredSystemLibraries)
endif()
