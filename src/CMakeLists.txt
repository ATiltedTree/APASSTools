find_package(Qt5 REQUIRED COMPONENTS Widgets Svg Network)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(
  APASSTools WIN32
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

target_link_libraries(APASSTools PRIVATE Qt5::Widgets Qt5::Svg Qt5::Network)

if(WIN32)
  target_sources(APASSTools PRIVATE assets/apasstools.rc)

  # Delegate to Qt's official deployment binary on Windows to copy over the necessary Qt-specific
  # libraries, etc.
  get_target_property(MOC_EXECUTABLE_LOCATION Qt5::moc IMPORTED_LOCATION)
  get_filename_component(QT_BINARY_DIRECTORY "${MOC_EXECUTABLE_LOCATION}" DIRECTORY)
  find_program(WINDEPLOYQT_EXE windeployqt HINTS "${QT_BINARY_DIRECTORY}")

  set(WINDEPLOYQT_ARGS
      "--no-translations
      --no-compiler-runtime
      --no-opengl-sw
      --no-system-d3d-compiler
      --no-angle
      --dry-run
      --list mapping
      $<IF:$<STREQUAL:${CMAKE_BUILD_TYPE},Release>,--release,--debug>
      $<TARGET_FILE:APASSTools>"
  )
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
