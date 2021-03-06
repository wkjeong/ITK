set(GDCM_TARGETS_NAME ${ITK-GDCM-targets})
set(GDCM_INSTALL_BIN_DIR ${ITK-GDCM_INSTALL_RUNTIME_DIR})
set(GDCM_INSTALL_LIB_DIR ${ITK-GDCM_INSTALL_LIBRARY_DIR})
set(GDCM_INSTALL_INCLUDE_DIR ${ITK-GDCM_INSTALL_INCLUDE_DIR})
set(GDCM_INSTALL_DATA_DIR ${ITK_INSTALL_DATA_DIR}/gdcm)
set(GDCM_BUILD_TESTING_DEFAULT OFF)

# Tell GDCM to use "system" libraries but give it ITK's libraries:
#
# Expat:
set(GDCM_USE_SYSTEM_EXPAT ON CACHE INTERNAL "")
set(EXPAT_INCLUDE_DIR ${ITK-Expat_INCLUDE_DIRS})
set(EXPAT_LIBRARY ${ITK-Expat_LIBRARIES})
# OpenJPEG:
set(GDCM_USE_SYSTEM_OPENJPEG ON CACHE INTERNAL "")
set(OPENJPEG_MAJOR_VERSION 2)
set(OPENJPEG_LIBRARY ${ITK-OpenJPEG_LIBRARIES})
set(OPENJPEG_LIBRARIES ${OPENJPEG_LIBRARY})
set(OPENJPEG_INCLUDE_DIR ${ITK-OpenJPEG_INCLUDE_DIRS})
# ZLIB:
set(GDCM_USE_SYSTEM_ZLIB ON CACHE INTERNAL "")
if(NOT ITK_USE_SYSTEM_ZLIB)
  set(ZLIB_INCLUDE_DIR ${ITK-ZLIB_SOURCE_DIR}/src/itkzlib)
  set(ZLIB_LIBRARY itkzlib)
endif()

# Configure GDCM privately so its options do not appear to the user.
set(GDCM_LEGACY_REMOVE OFF CACHE INTERNAL "Remove all legacy code completely.")
set(GDCM_LEGACY_SILENT OFF CACHE INTERNAL "Silence all legacy code messages.")
set(GDCM_SUPPORT_BROKEN_IMPLEMENTATION ON CACHE INTERNAL "Handle broken DICOM")
set(GDCM_TEMP_DIRECTORY "${ITK_TEST_OUTPUT_DIR}" CACHE INTERNAL "Path to a valid temp directory")
set(GDCM_USE_KAKADU OFF CACHE INTERNAL "Use kakadu lib, only turn it on if you know what you are doing.")
set(GDCM_USE_PVRG OFF CACHE INTERNAL "Use pvrg lib, only turn it on if you know what you are doing.")
set(GDCM_USE_SYSTEM_LJPEG OFF CACHE INTERNAL "Use system ljpeg (ijg lib)")
set(GDCM_USE_SYSTEM_OPENSSL OFF CACHE INTERNAL "Use system OpenSSL")
set(GDCM_USE_SYSTEM_PODOFO OFF CACHE INTERNAL "Use system podofo (pdf)")
set(GDCM_USE_SYSTEM_POPPLER OFF CACHE INTERNAL "Use system poppler (pdf)")
set(GDCM_USE_SYSTEM_UUID OFF CACHE INTERNAL "Use system uuid")
set(GDCM_USE_WXWIDGETS OFF CACHE INTERNAL "wxWidgets bridge ?")
set(GDCM_WRITE_ODD_LENGTH OFF CACHE INTERNAL "Do not change")

# GDCM uses these to refer to executable and library locations
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(LIBRARY_OUTPUT_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_subdirectory(gdcm)

foreach(lib
    gdcmCommon
    gdcmDICT
    gdcmDSED
    gdcmIOD
    gdcmMSFF
    gdcmcharls
    gdcmjpeg12
    gdcmjpeg16
    gdcmjpeg8
    gdcmuuid
    )
  if(TARGET ${lib}) # some gdcm targets are conditional
    itk_module_target(${lib} NO_INSTALL)
  endif()
endforeach()
