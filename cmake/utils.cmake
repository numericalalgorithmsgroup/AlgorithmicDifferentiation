FUNCTION(dco_print_all_variables)
  get_cmake_property(_variableNames VARIABLES)
  list (SORT _variableNames)
  foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
  endforeach()
ENDFUNCTION()

MACRO(DCO_GET_SUBDIRS dir result)
  FILE(GLOB children RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

FUNCTION(dco_get_test_name out_cur_name from_file)
  GET_FILENAME_COMPONENT(cur_abs_path ${from_file} ABSOLUTE)
  GET_FILENAME_COMPONENT(cur_dir ${cur_abs_path} DIRECTORY)

  STRING(REPLACE ${CMAKE_BINARY_DIR}/ "" cur_dir ${cur_dir})
  STRING(REPLACE ${CMAKE_BINARY_DIR}  "" cur_dir ${cur_dir})
  STRING(REPLACE ${CMAKE_SOURCE_DIR}/ "" cur_dir ${cur_dir})
  STRING(REPLACE ${CMAKE_SOURCE_DIR}  "" cur_dir ${cur_dir})
  
  STRING(REPLACE ${CMAKE_SOURCE_DIR}/ "" cur_name ${cur_dir})
  STRING(REPLACE "/" "." cur_name ${cur_name})

  SET(${out_cur_name} ${cur_name} PARENT_SCOPE)
ENDFUNCTION()


