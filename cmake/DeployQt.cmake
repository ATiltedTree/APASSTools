macro(deploy_qt args)
  if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Delegate to Qt's official deployment binary to copy over the necessary
    # Qt-specific libraries, etc.
    get_target_property(MOC_EXECUTABLE_LOCATION Qt5::moc IMPORTED_LOCATION)
    get_filename_component(
      QT_BINARY_DIRECTORY "${MOC_EXECUTABLE_LOCATION}" DIRECTORY
    )

    find_program(
      DEPLOY_QT
      NAMES windeployqt macdeployqt
      HINTS "${QT_BINARY_DIRECTORY}"
    )

    install(CODE "execute_process(COMMAND \"${DEPLOY_QT}\" \"${args}\")"
            COMPONENT Runtime
    )

  endif()
endmacro()
