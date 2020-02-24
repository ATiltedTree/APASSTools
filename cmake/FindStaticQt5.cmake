include(FindPackageHandleStandardArgs)

find_package(Qt5Core REQUIRED)

foreach(module ${StaticQt5_FIND_COMPONENTS})
  find_package(StaticQt5${module} ${StaticQt5_FIND_REQUIRED} ${StaticQt5_FIND_QUIETLY})
  find_package_handle_standard_args(StaticQt5${module} CONFIG_MODE)
endforeach()


