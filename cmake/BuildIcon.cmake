macro(build_icon target src icon_sizes)
  if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")

    find_program(CONVERT convert)

    add_custom_command(
      OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/icons"
      COMMAND "${CMAKE_COMMAND}" -E make_directory
              "${CMAKE_CURRENT_BINARY_DIR}/icons"
    )
    if(APPLE)
      find_program(ICONUTIL iconutil)

      set(ICON "${CMAKE_CURRENT_BINARY_DIR}/${target}.icns")

      foreach(ICON_SIZE ${icon_sizes})
        add_custom_command(
          DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/icons"
          OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}.png"
          COMMAND
            "${CONVERT}" -background none -resize ${ICON_SIZE}x${ICON_SIZE}
            "${src}"
            "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}.png"
        )
        math(EXPR DOUBLE_SIZE "${ICON_SIZE} * 2")
        add_custom_command(
          DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/icons"
          OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
          COMMAND
            "${CONVERT}" -background none -resize ${DOUBLE_SIZE}x${DOUBLE_SIZE}
            "${src}"
            "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
        )
        list(
          APPEND
          ICONS
          "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}.png"
          "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}@2.png"
        )
      endforeach()

      add_custom_command(
        OUTPUT "${ICON}"
        DEPENDS ${ICONS}
        COMMAND "${ICONUTIL}" --convert icns
                "${CMAKE_CURRENT_BINARY_DIR}/icons" --output "${ICON}"
      )
    elseif(WIN32)

      set(ICON "${CMAKE_CURRENT_BINARY_DIR}/${target}.ico")

      foreach(ICON_SIZE ${icon_sizes})
        add_custom_command(
          DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/icons"
          OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}.png"
          COMMAND
            "${CONVERT}" -background none -resize ${ICON_SIZE}x${ICON_SIZE}
            "${src}"
            "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}.png"
        )
        list(
          APPEND ICONS
          "${CMAKE_CURRENT_BINARY_DIR}/icons/icon_${ICON_SIZE}x${ICON_SIZE}.png"
        )
      endforeach()

      add_custom_command(
        OUTPUT "${ICON}"
        DEPENDS ${ICONS}
        COMMAND "${CONVERT}" "${CMAKE_CURRENT_BINARY_DIR}/icons/*" "${ICON}"
      )

    endif()
  endif()
endmacro()
