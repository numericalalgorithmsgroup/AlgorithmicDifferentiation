FUNCTION(get_prod prodcode INSTALL_PATH)
  IF (IS_WINDOWS)
    SET(appid \{8B8241FE-4770-49CB-B334-1E6${prodcode}\}_is1)
    execute_process(COMMAND "reg" "query" "HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\${appid}" OUTPUT_VARIABLE INSTALL_PATH_LOC ERROR_QUIET)
    IF (INSTALL_PATH_LOC)
      string(REGEX MATCH "InstallLocation[ ]*REG_SZ[ ]*([^\n]*)" INSTALL_PATH_LOC ${INSTALL_PATH_LOC})
      string(REGEX REPLACE "InstallLocation[ ]*REG_SZ[ ]*" "" INSTALL_PATH_LOC ${INSTALL_PATH_LOC})
    ENDIF()
    SET(${INSTALL_PATH} ${INSTALL_PATH_LOC} PARENT_SCOPE)
  ELSE()
    # search default installation directories
    SET(DEF_DIRS $ENV{HOME}/NAG/${prodcode} /opt/NAG/${prodcode} /opt/${prodcode})
    find_file(INSTALL_PATH_LOC dco.hpp PATHS ${DEF_DIRS} NO_DEFAULT_PATH PATH_SUFFIXES include)
    IF (INSTALL_PATH_LOC)
      get_filename_component(INSTALL_PATH_LOC ${INSTALL_PATH_LOC} DIRECTORY)
      string(REPLACE "/include" "" INSTALL_PATH_LOC ${INSTALL_PATH_LOC})
    ENDIF()
    SET(${INSTALL_PATH} ${INSTALL_PATH_LOC} PARENT_SCOPE)
  ENDIF()
  UNSET(INSTALL_PATH_LOC CACHE)
ENDFUNCTION()

include(arch)
get_architecture(IS_LINUX IS_WINDOWS IS_64 IS_32)

SET(DCO_CPP_BASE_DIR "" CACHE STRING "installation path of dco/c++")

## try to find local dco/c++ version
####################################
IF (NOT(DCO_CPP_BASE_DIR))
  UNSET(DCO_CPP_INCLUDE_DIR CACHE)
  UNSET(DCO_CPP_LIBRARY CACHE)
  find_path(DCO_CPP_INCLUDE_DIR dco.hpp HINTS
    ${CMAKE_SOURCE_DIR}/dco_cpp_dev
    ${CMAKE_SOURCE_DIR}
    $ENV{HOME}/dco_cpp_dev
    $ENV{HOME}/dco
    $ENV{HOME}/dco/dco_cpp_dev
    $ENV{HOME}/git/dco_cpp_dev
    $ENV{HOME}/mygit/dco_cpp_dev
    $ENV{HOME}/Software/dco_cpp_dev
    PATH_SUFFIXES
    src
    include
    )

  IF(DCO_CPP_INCLUDE_DIR)
    SET(DCO_CPP_BASE_DIR ${DCO_CPP_INCLUDE_DIR}/..)
    get_filename_component(DCO_CPP_BASE_DIR "${DCO_CPP_BASE_DIR}" ABSOLUTE)
  ENDIF()
ENDIF()

## try to find dco/c++ in common places
#######################################
IF (NOT(DCO_CPP_BASE_DIR))
  UNSET(DCO_CPP_INCLUDE_DIR CACHE)
  UNSET(DCO_CPP_LIBRARY CACHE)
  IF (IS_WINDOWS)
    # Determine Visual Studio Version
    if(CMAKE_C_COMPILER_VERSION MATCHES "16.0(.*)")
      SET(PLATFORMTOOLSET v100)
      SET(VISUAL_STUDIO_VERSION 10)
    ELSEIF(CMAKE_C_COMPILER_VERSION MATCHES "17.0(.*)")
      SET(PLATFORMTOOLSET v110)
      SET(VISUAL_STUDIO_VERSION 12)
    ELSEIF(CMAKE_C_COMPILER_VERSION MATCHES "18.0(.*)")
      SET(PLATFORMTOOLSET v120)
      SET(VISUAL_STUDIO_VERSION 13)
    ELSEIF(CMAKE_C_COMPILER_VERSION MATCHES "19.0(.*)")
      SET(PLATFORMTOOLSET v140)
      SET(VISUAL_STUDIO_VERSION 15)
    ELSEIF(CMAKE_C_COMPILER_VERSION MATCHES "19.1(.*)")
      SET(PLATFORMTOOLSET v141)
      SET(VISUAL_STUDIO_VERSION 17)
    ENDIF ()

    FOREACH (version_major 6 5 4 3 2)
      IF (DCO_CPP_BASE_DIR)
	break()
      ENDIF()
      FOREACH (version_minor 9 8 7 6 5 4 3 2 1 0)
	get_prod(dcwin${version_major}${version_minor}nn DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR)
	  break()
	ENDIF()

	get_prod(dcw6i${version_major}${version_minor}na DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15))
	  MESSAGE(STATUS "dco/c++: VS pre 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND IS_32)
	  MESSAGE(STATUS "dco/c++: 64-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15 AND IS_64)
	  break()
	ENDIF()

	get_prod(dcw6i${version_major}${version_minor}ne DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15)
	  MESSAGE(STATUS "dco/c++: VS post 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND IS_32)
	  MESSAGE(STATUS "dco/c++: 64-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15) AND IS_64)
	  break()
	ENDIF()

	get_prod(dcw32${version_major}${version_minor}na DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15))
	  MESSAGE(STATUS "dco/c++: VS pre 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND IS_64)
	  MESSAGE(STATUS "dco/c++: 32-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15 AND IS_64)
	  break()
	ENDIF()

	get_prod(dcw32${version_major}${version_minor}ne DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15)
	  MESSAGE(STATUS "dco/c++: VS post 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND IS_64)
	  MESSAGE(STATUS "dco/c++: 32-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15) AND IS_32)
	  break()
	ENDIF()

      ENDFOREACH()
    ENDFOREACH()

  ELSE() ## LINUX
    FOREACH (version_major 6 5 4 3 2)
      IF (DCO_CPP_BASE_DIR)
	break()
      ENDIF()
      FOREACH (version_minor 9 8 7 6 5 4 3 2 1 0)
	get_prod(dclin${version_major}${version_minor}nn DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR)
	  break()
	ENDIF()
	get_prod(dcl6i${version_major}${version_minor}ngl DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR AND IS_64)
	  break()
	ENDIF()
	get_prod(dclux${version_major}${version_minor}ngl DCO_CPP_BASE_DIR)
	IF (DCO_CPP_BASE_DIR AND IS_64)
	  MESSAGE(STATUS "dco/c++: 32-bit version found here: '${DCO_CPP_BASE_DIR}'. Continue searching. \
If you really want to use this 32-bit version on your 64-bit system, \
please specify DCO_CPP_BASE_DIR explicitly. ")
	ENDIF()
	IF (DCO_CPP_BASE_DIR AND IS_32)
	  break()
	ENDIF()
      ENDFOREACH()
    ENDFOREACH()
  ENDIF()
ENDIF()

## find path to dco.hpp
#######################
find_path(DCO_CPP_INCLUDE_DIR dco.hpp HINTS
  ${DCO_CPP_BASE_DIR}/include
  ${DCO_CPP_BASE_DIR}/src
  ${DCO_CPP_BASE_DIR})
mark_as_advanced(DCO_CPP_INCLUDE_DIR)

## get dco/c++ version number
#############################
SET(DCO_CPP_VERSION_MAJOR "0")
SET(DCO_CPP_VERSION_MINOR "0")
find_file(DCO_CPP_VERSION_HPP dco_version.hpp HINTS
  ${DCO_CPP_BASE_DIR}/include
  ${DCO_CPP_BASE_DIR}/src
  ${DCO_CPP_BASE_DIR})
IF (DCO_CPP_VERSION_HPP)
  file(READ ${DCO_CPP_VERSION_HPP} FILE_CONTENTS)
  string(REGEX REPLACE ".*#define DCO_VERSION_SHORT [v]*\([0-9].[0-9]\).*" "\\1"
    VERSION ${FILE_CONTENTS})
  string(REGEX REPLACE "\([0-9]\).[0-9]" "\\1" DCO_CPP_VERSION_MAJOR ${VERSION})
  string(REGEX REPLACE "[0-9].\([0-9]\)" "\\1" DCO_CPP_VERSION_MINOR ${VERSION})
ENDIF()
UNSET(DCO_CPP_VERSION_HPP CACHE)

## licensed version => search library
#####################################
IF (IS_WINDOWS)
  find_library(DCO_CPP_LIBRARY NAMES libdcoc_MT HINTS ${DCO_CPP_BASE_DIR}/lib)
ELSE()
  find_library(DCO_CPP_LIBRARY NAMES dcoc HINTS ${DCO_CPP_BASE_DIR}/lib)
ENDIF()
get_filename_component(DCO_CPP_LIBRARY_DIR ${DCO_CPP_LIBRARY} DIRECTORY)
IF (DCO_CPP_LIBRARY)
  SET(DCO_CPP_LIBRARIES ${DCO_CPP_LIBRARY})
  mark_as_advanced(DCO_CPP_LIBRARIES)
ELSE()
  UNSET(DCO_CPP_LIBRARIES CACHE)
  UNSET(DCO_CPP_LIBRARY_DIR CACHE)
ENDIF()
UNSET(DCO_CPP_LIBRARY CACHE)
  

## finalize find_package with some output
#########################################
IF ("${DCO_CPP_VERSION_MAJOR}.${DCO_CPP_VERSION_MINOR}" LESS "${dco_cpp_FIND_VERSION_MAJOR}.${dco_cpp_FIND_VERSION_MINOR}")
  MESSAGE(FATAL_ERROR "dco/c++: not found. Required version ${dco_cpp_FIND_VERSION_MAJOR}.${dco_cpp_FIND_VERSION_MINOR} larger than detected ${DCO_CPP_VERSION_MAJOR}.${DCO_CPP_VERSION_MINOR}. Set DCO_CPP_BASE_DIR respectively.")
ENDIF()

IF (NOT(DCO_CPP_INCLUDE_DIR))
  SET(dco_cpp_FOUND 0)
  IF (dco_cpp_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "dco/c++: not found. Set DCO_CPP_BASE_DIR respectively.")
  ELSE()
    MESSAGE(WARNING "dco/c++: not found. Set DCO_CPP_BASE_DIR respectively.")
  ENDIF()
ELSE()
  IF(DCO_CPP_BASE_DIR)
    MESSAGE(STATUS "Found dco/c++: Picking v${DCO_CPP_VERSION_MAJOR}.${DCO_CPP_VERSION_MINOR} in '${DCO_CPP_BASE_DIR}'.")
  ENDIF()
  SET(DCO_CPP_BASE_DIR ${DCO_CPP_BASE_DIR} CACHE STRING "" FORCE)
  SET(DCO_CPP_VERSION_MAJOR ${DCO_CPP_VERSION_MAJOR} CACHE STRING "" FORCE)
  SET(DCO_CPP_VERSION_MINOR ${DCO_CPP_VERSION_MINOR} CACHE STRING "" FORCE)
  mark_as_advanced(DCO_CPP_VERSION_MAJOR)
  mark_as_advanced(DCO_CPP_VERSION_MINOR)
  SET(dco_cpp_FOUND 1)
ENDIF()

