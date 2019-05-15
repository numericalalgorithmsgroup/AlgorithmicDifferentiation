function(get_prod prodcode INSTALL_PATH)
  if (IS_WINDOWS)
    set(appid \{8B8241FE-4770-49CB-B334-1E6${prodcode}\}_is1)
    execute_process(COMMAND "reg" "query" "HKLM\\SOFTWARE\\WOW6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\${appid}" OUTPUT_VARIABLE INSTALL_PATH_LOC ERROR_QUIET)
    if (INSTALL_PATH_LOC)
      string(REGEX MATCH "InstallLocation[ ]*REG_SZ[ ]*([^\n]*)" INSTALL_PATH_LOC ${INSTALL_PATH_LOC})
      string(REGEX REPLACE "InstallLocation[ ]*REG_SZ[ ]*" "" INSTALL_PATH_LOC ${INSTALL_PATH_LOC})
    endif()
    set(${INSTALL_PATH} ${INSTALL_PATH_LOC} PARENT_SCOPE)
  else()
    # search default installation directories
    set(DEF_DIRS $ENV{HOME}/NAG/${prodcode} /opt/NAG/${prodcode} /opt/${prodcode})
    find_file(INSTALL_PATH_LOC dco.hpp PATHS ${DEF_DIRS} NO_DEFAULT_PATH PATH_SUFFIXES include)
    if (INSTALL_PATH_LOC)
      get_filename_component(INSTALL_PATH_LOC ${INSTALL_PATH_LOC} DIRECTORY)
      string(REPLACE "/include" "" INSTALL_PATH_LOC ${INSTALL_PATH_LOC})
    endif()
    set(${INSTALL_PATH} ${INSTALL_PATH_LOC} PARENT_SCOPE)
  endif()
  unset(INSTALL_PATH_LOC CACHE)
endfunction()

include(arch)
get_architecture(IS_LINUX IS_WINDOWS IS_64 IS_32)

set(DCO_CPP_BASE_DIR "" CACHE STRING "installation path of dco/c++")

## try to find local dco/c++ version
####################################
IF (NOT(DCO_CPP_BASE_DIR))
  unset(DCO_CPP_INCLUDE_DIR CACHE)
  unset(DCO_CPP_LIBRARY CACHE)
  find_path(DCO_CPP_INCLUDE_DIR dco.hpp HINTS
    ${CMAKE_SOURCE_DIR}/dco_cpp_dev/src
    ${CMAKE_SOURCE_DIR}/src)

  IF(DCO_CPP_INCLUDE_DIR)
    set(DCO_CPP_BASE_DIR ${DCO_CPP_INCLUDE_DIR}/..)
    get_filename_component(DCO_CPP_BASE_DIR "${DCO_CPP_BASE_DIR}"
      ABSOLUTE)
  ENDIF()
ENDIF()

## try to find dco/c++ in common places
#######################################
IF (NOT(DCO_CPP_BASE_DIR))
  unset(DCO_CPP_INCLUDE_DIR CACHE)
  unset(DCO_CPP_LIBRARY CACHE)
  IF (IS_WINDOWS)
    # Determine Visual Studio Version
    if(CMAKE_C_COMPILER_VERSION MATCHES "16.0(.*)")
      set(PLATFORMTOOLSET v100)
      set(VISUAL_STUDIO_VERSION 10)
    elseif(CMAKE_C_COMPILER_VERSION MATCHES "17.0(.*)")
      set(PLATFORMTOOLSET v110)
      set(VISUAL_STUDIO_VERSION 12)
    elseif(CMAKE_C_COMPILER_VERSION MATCHES "18.0(.*)")
      set(PLATFORMTOOLSET v120)
      set(VISUAL_STUDIO_VERSION 13)
    elseif(CMAKE_C_COMPILER_VERSION MATCHES "19.0(.*)")
      set(PLATFORMTOOLSET v140)
      set(VISUAL_STUDIO_VERSION 15)
    elseif(CMAKE_C_COMPILER_VERSION MATCHES "19.1(.*)")
      set(PLATFORMTOOLSET v141)
      set(VISUAL_STUDIO_VERSION 17)
    endif ()

    foreach (version_major 6 5 4 3 2)
      if (DCO_CPP_BASE_DIR)
	break()
      endif()
      foreach (version_minor 9 8 7 6 5 4 3 2 1 0)
	get_prod(dcwin${version_major}${version_minor}nn DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR)
	  break()
	endif()

	get_prod(dcw6i${version_major}${version_minor}na DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15))
	  MESSAGE(STATUS "dco/c++: VS pre 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND IS_32)
	  MESSAGE(STATUS "dco/c++: 64-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15 AND IS_64)
	  break()
	endif()

	get_prod(dcw6i${version_major}${version_minor}ne DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15)
	  MESSAGE(STATUS "dco/c++: VS post 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND IS_32)
	  MESSAGE(STATUS "dco/c++: 64-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15) AND IS_64)
	  break()
	endif()

	get_prod(dcw32${version_major}${version_minor}na DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15))
	  MESSAGE(STATUS "dco/c++: VS pre 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND IS_64)
	  MESSAGE(STATUS "dco/c++: 32-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15 AND IS_64)
	  break()
	endif()

	get_prod(dcw32${version_major}${version_minor}ne DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR AND VISUAL_STUDIO_VERSION LESS 15)
	  MESSAGE(STATUS "dco/c++: VS post 2015 version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND IS_64)
	  MESSAGE(STATUS "dco/c++: 32-bit version found here: '${DCO_CPP_BASE_DIR}'. This is not matching your currently loaded environment. Continue searching.")
	endif()
	if (DCO_CPP_BASE_DIR AND NOT(VISUAL_STUDIO_VERSION LESS 15) AND IS_32)
	  break()
	endif()

      endforeach()
    endforeach()

  ELSE() ## LINUX
    foreach (version_major 6 5 4 3 2)
      if (DCO_CPP_BASE_DIR)
	break()
      endif()
      foreach (version_minor 9 8 7 6 5 4 3 2 1 0)
	get_prod(dclin${version_major}${version_minor}nn DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR)
	  break()
	endif()
	get_prod(dcl6i${version_major}${version_minor}ngl DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR AND IS_64)
	  break()
	endif()
	get_prod(dclux${version_major}${version_minor}ngl DCO_CPP_BASE_DIR)
	if (DCO_CPP_BASE_DIR AND IS_64)
	  MESSAGE(STATUS "dco/c++: 32-bit version found here: '${DCO_CPP_BASE_DIR}'. Continue searching. \
If you really want to use this 32-bit version on your 64-bit system, \
please specify DCO_CPP_BASE_DIR explicitly. ")
	endif()
	if (DCO_CPP_BASE_DIR AND IS_32)
	  break()
	endif()
      endforeach()
    endforeach()
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
set(DCO_CPP_VERSION_MAJOR "0")
set(DCO_CPP_VERSION_MINOR "0")
find_file(DCO_CPP_VERSION_HPP dco_version.hpp HINTS
  ${DCO_CPP_BASE_DIR}/include
  ${DCO_CPP_BASE_DIR}/src
  ${DCO_CPP_BASE_DIR})
if (DCO_CPP_VERSION_HPP)
  file(READ ${DCO_CPP_VERSION_HPP} FILE_CONTENTS)
  string(REGEX REPLACE ".*#define DCO_VERSION_SHORT [v]*\([0-9].[0-9]\).*" "\\1"
    VERSION ${FILE_CONTENTS})
  string(REGEX REPLACE "\([0-9]\).[0-9]" "\\1" DCO_CPP_VERSION_MAJOR ${VERSION})
  string(REGEX REPLACE "[0-9].\([0-9]\)" "\\1" DCO_CPP_VERSION_MINOR ${VERSION})
endif()
unset(DCO_CPP_VERSION_HPP CACHE)

## licensed version => search library
#####################################
IF (IS_WINDOWS)
  find_library(DCO_CPP_LIBRARY NAMES libdcoc_MT HINTS ${DCO_CPP_BASE_DIR}/lib)
ELSE()
  find_library(DCO_CPP_LIBRARY NAMES dcoc HINTS ${DCO_CPP_BASE_DIR}/lib)
ENDIF()
get_filename_component(DCO_CPP_LIBRARY_DIR ${DCO_CPP_LIBRARY} DIRECTORY)
if (DCO_CPP_LIBRARY)
  set(DCO_CPP_LIBRARIES ${DCO_CPP_LIBRARY})
  mark_as_advanced(DCO_CPP_LIBRARIES)
else()
  unset(DCO_CPP_LIBRARIES CACHE)
  unset(DCO_CPP_LIBRARY_DIR CACHE)
endif()
unset(DCO_CPP_LIBRARY CACHE)
  

## finalize find_package with some output
#########################################
if (NOT(DCO_CPP_INCLUDE_DIR))
  set(dco_cpp_FOUND 0)
  if (dco_cpp_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "dco/c++: not found. Set DCO_CPP_BASE_DIR respectively.")
  else()
    MESSAGE(WARNING "dco/c++: not found. Set DCO_CPP_BASE_DIR respectively.")
  endif()
else()
  IF(DCO_CPP_BASE_DIR)
    MESSAGE(STATUS "Found dco/c++: Picking v${DCO_CPP_VERSION_MAJOR}.${DCO_CPP_VERSION_MINOR} in '${DCO_CPP_BASE_DIR}'.")
  ENDIF()
  set(DCO_CPP_BASE_DIR ${DCO_CPP_BASE_DIR} CACHE STRING "" FORCE)
  set(DCO_CPP_VERSION_MAJOR ${DCO_CPP_VERSION_MAJOR} CACHE STRING "" FORCE)
  set(DCO_CPP_VERSION_MINOR ${DCO_CPP_VERSION_MINOR} CACHE STRING "" FORCE)
  mark_as_advanced(DCO_CPP_VERSION_MAJOR)
  mark_as_advanced(DCO_CPP_VERSION_MINOR)
  set(dco_cpp_FOUND 1)
endif()

