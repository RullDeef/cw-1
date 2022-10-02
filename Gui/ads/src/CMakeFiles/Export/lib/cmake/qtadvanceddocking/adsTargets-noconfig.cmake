#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "ads::qtadvanceddocking" for configuration ""
set_property(TARGET ads::qtadvanceddocking APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(ads::qtadvanceddocking PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libqtadvanceddocking.so.3.7.0"
  IMPORTED_SONAME_NOCONFIG "libqtadvanceddocking.so.3.7.0"
  )

list(APPEND _IMPORT_CHECK_TARGETS ads::qtadvanceddocking )
list(APPEND _IMPORT_CHECK_FILES_FOR_ads::qtadvanceddocking "${_IMPORT_PREFIX}/lib/libqtadvanceddocking.so.3.7.0" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
