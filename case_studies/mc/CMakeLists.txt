set(SUBDIRS a1s a1s_ensemble a1s_preaccumulator cfd primal socfd t1s t2s_a1s t2s_a1s_ensemble t2s_t1s)
foreach (cs ${SUBDIRS})
  DCO_ADD_CASE_STUDY("${CMAKE_CURRENT_SOURCE_DIR}/scenario_1.in" ${cs}/main.cpp)
endforeach()

set(DCO_SRC_FILES main.cpp)
set(DCO_INCLUDE_LEVEL ../../..)

## installation
if (DCO_BUILD_CASE_STUDIES)
  # used in configure below
  JOIN("${SUBDIRS}" " " SUBDIRS_STRING)

  # create top-level makefiles and install
  configure_file(
    ${CMAKE_SOURCE_DIR}/additionals/build_templates/${EXAMPLES_TEMPLATE}
    ${CMAKE_BINARY_DIR}/tmp_files/case_studies/mc/Makefile
    @ONLY
    )
  install(
    FILES ${CMAKE_BINARY_DIR}/tmp_files/case_studies/mc/Makefile
    DESTINATION case_studies/mc/
    )

  set(DCO_EXE_PARAMETERS ../scenario_1.in)
  foreach(subsubdir ${SUBDIRS})

    # install ref_results file
    FIND_REF_RESULT_FILE("${subsubdir}/" 1)
    if (${FILE_FOUND})
      set(FILE_COMPARE_COMMAND_MAKEFILE "${FILE_COMPARE_COMMAND} out ref_results")
      install(
        FILES ${REF_RES_FILE}
        DESTINATION case_studies/mc/${subsubdir}
        RENAME ref_results
      )
    else()
        set(FILE_COMPARE_COMMAND_MAKEFILE "")
    endif()
    
    # create makefile for each example and install
    configure_file(
      ${CMAKE_SOURCE_DIR}/additionals/build_templates/${SINGLE_EXAMPLE_TEMPLATE}
      ${CMAKE_BINARY_DIR}/tmp_files/case_studies/mc/${subsubdir}/Makefile
      @ONLY
      )
    install(
      FILES ${CMAKE_BINARY_DIR}/tmp_files/case_studies/mc/${subsubdir}/Makefile
      DESTINATION case_studies/mc/${subsubdir}
      )

    # Visual Studio files
    CREATE_VS_VCXPROJ_FILE(case_studies/mc ${subsubdir} SLN_PROJECT SLN_POST)
  endforeach()

  # copy example source and header files
  install_with_copyright(DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION case_studies TARGET case_studies.mc)
  install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION case_studies
    FILES_MATCHING 
    PATTERN "*.in"
    PATTERN "approx_results"
    PATTERN "README"
    )

  # Top level Visual Studio Files
  CREATE_VS_SLN_FILES(case_studies/mc)
endif()
  
