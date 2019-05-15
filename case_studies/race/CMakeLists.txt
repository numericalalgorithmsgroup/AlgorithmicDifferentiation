## compilation and testing
set(SUBDIRS cfd ga1s ga1v ga2s_ga1s ga2s_gt1s gt1s gt1v gt2s_ga1s gt2s_gt1s socfd)

foreach(cs ${SUBDIRS})
  if (${cs} MATCHES gt1v)
    DCO_ADD_CASE_STUDY("100" ${cs}/main.cpp)
  else()
    DCO_ADD_CASE_STUDY("5" ${cs}/main.cpp)
  endif()
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
    ${CMAKE_BINARY_DIR}/tmp_files/case_studies/race/Makefile
    @ONLY
    )
  install(
    FILES ${CMAKE_BINARY_DIR}/tmp_files/case_studies/race/Makefile
    DESTINATION case_studies/race/
    )

  foreach(subsubdir ${SUBDIRS})
    # parameters different for gt1v test
    if (${subsubdir} MATCHES gt1v)
      set(DCO_EXE_PARAMETERS 100)
    else()
      set(DCO_EXE_PARAMETERS 5)
    endif()

    # install ref_results file
    FIND_REF_RESULT_FILE("${subsubdir}/" 1)
    if (${FILE_FOUND})
      set(FILE_COMPARE_COMMAND_MAKEFILE "${FILE_COMPARE_COMMAND} out ref_results")
      install(
        FILES ${REF_RES_FILE}
        DESTINATION case_studies/race/${subsubdir}
        RENAME ref_results
      )
    else()
        set(FILE_COMPARE_COMMAND_MAKEFILE "")
    endif()
    
    # create makefile for each example and install
    configure_file(
      ${CMAKE_SOURCE_DIR}/additionals/build_templates/${SINGLE_EXAMPLE_TEMPLATE}
      ${CMAKE_BINARY_DIR}/tmp_files/case_studies/race/${subsubdir}/Makefile
      @ONLY
      )
    install(
      FILES ${CMAKE_BINARY_DIR}/tmp_files/case_studies/race/${subsubdir}/Makefile
      DESTINATION case_studies/race/${subsubdir}
      )

    # Visual Studio files
    CREATE_VS_VCXPROJ_FILE(case_studies/race ${subsubdir} SLN_PROJECT SLN_POST)
  endforeach()

  # copy example source and header files
  install_with_copyright(DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION case_studies TARGET case_studies.race)
  install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION case_studies
    FILES_MATCHING 
    PATTERN "*.in"
    PATTERN "approx_results"
    PATTERN "README"
    )

  # Top level Visual Studio Files
  CREATE_VS_SLN_FILES(case_studies/race)
endif()


