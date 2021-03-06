macro(build_icon target src icon_sizes)
  if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")

    find_program(
      MAGICK
      NAMES magick
      PATHS "[HKEY_LOCAL_MACHINE\\SOFTWARE\\ImageMagick\\Current;BinPath]"
    )

    if(APPLE)
      set(ICON_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/icons/${target}.iconset")
      set(ICON "${CMAKE_CURRENT_BINARY_DIR}/icons/${target}.icns")

      find_program(ICONUTIL iconutil)

      execute_process(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${ICON_FOLDER}"
      )

      foreach(ICON_SIZE ${icon_sizes})
        add_custom_command(
          OUTPUT "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}.png"
          COMMAND
            "${MAGICK}" convert -background none -size
            ${ICON_SIZE}x${ICON_SIZE} "${src}"
            "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}.png"
        )
        math(EXPR DOUBLE_SIZE "${ICON_SIZE} * 2")
        add_custom_command(
          OUTPUT "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
          COMMAND
            "${MAGICK}" convert -background none -size
            ${DOUBLE_SIZE}x${DOUBLE_SIZE} "${src}"
            "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
        )
        list(APPEND ICONS "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}.png"
             "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
        )
      endforeach()

      add_custom_command(
        OUTPUT "${ICON}"
        DEPENDS ${ICONS}
        COMMAND "${ICONUTIL}" --convert icns "${ICON_FOLDER}" --output
                "${ICON}"
      )
    elseif(WIN32)
      set(ICON_FOLDER "${CMAKE_CURRENT_BINARY_DIR}/icons/${target}")
      set(ICON "${CMAKE_CURRENT_BINARY_DIR}/icons/${target}.ico")

      execute_process(
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${ICON_FOLDER}"
      )

      foreach(ICON_SIZE ${icon_sizes})
        add_custom_command(
          OUTPUT "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}.png"
          COMMAND
            "${MAGICK}" convert -background none -size
            ${ICON_SIZE}x${ICON_SIZE} "${src}"
            "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}.png"
        )
        list(APPEND ICONS "${ICON_FOLDER}/icon_${ICON_SIZE}x${ICON_SIZE}.png")
      endforeach()

      add_custom_command(
        OUTPUT "${ICON}"
        DEPENDS ${ICONS}
        COMMAND "${MAGICK}" convert "${ICON_FOLDER}/*" "${ICON}"
      )
    endif()
  endif()
endmacro()
