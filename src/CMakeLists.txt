find_package(Qt5 REQUIRED COMPONENTS Widgets Svg Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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
  assets/assets.qrc
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
  target_sources(APASSTools PRIVATE assets/assets.rc)

  # Workaround because 'InstallRequiredSystemLibraries' does not install them when we are not using
  # MSVC and copying them over is just not an option
  if(NOT MSVC)
    target_link_libraries(APASSTools PRIVATE -static -static-libstdc++ -static-libgcc)
  endif()

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

    add_custom_command(
      TARGET APASSTools
      POST_BUILD
      COMMAND
        "${CMAKE_COMMAND}" -E env PATH="${QT_BINARY_DIRECTORY}" "${WINDEPLOYQT_EXE}"
        $<IF:$<CONFIG:Debug>,--debug,--release> --no-translations --no-compiler-runtime --no-angle
        --no-opengl-sw "$<TARGET_FILE:APASSTools>"
    )

  endif()
endif()

install(TARGETS APASSTools)
if(UNIX)
  install(FILES ${CMAKE_SOURCE_DIR}/LICENSE DESTINATION share/doc/APASSTools)
  install(FILES ${CMAKE_SOURCE_DIR}/APASSTools.desktop DESTINATION share/applications)
  install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/assets/icons/logo.svg
    DESTINATION share/icons/hicolor/scalable/apps
    RENAME apasstools.svg
  )
elseif(WIN32)
  install(
    CODE "
  execute_process(
    COMMAND
      \"${CMAKE_COMMAND}\" -E env PATH=\"${QT_BINARY_DIRECTORY}\" \"${WINDEPLOYQT_EXE}\"
      --dry-run
      --no-translations
      --no-compiler-runtime
      --no-angle
      --no-opengl-sw
      --release
      --list mapping
      \"${CMAKE_BINARY_DIR}/bin/APASSTools.exe\"
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
  include(InstallRequiredSystemLibraries)
  foreach(lib ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
    get_filename_component(filename "${lib}" NAME)
    add_custom_command(
      TARGET APASSTools
      POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${lib}" \"$<TARGET_FILE_DIR:APASSTools>\"
    )
  endforeach()
endif()
