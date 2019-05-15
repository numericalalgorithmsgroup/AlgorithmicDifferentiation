# different parameters
set(SUBDIRS_1_PARAMETERS 10 100)
set(SUBDIRS_1 obs f fd gt1s ga1s ga1s_sls sofd gt2s_gt1s gt2s_ga1s gt2s_ga1s_sls)
FOREACH(subdir ${SUBDIRS_1})
  DCO_ADD_CASE_STUDY("${SUBDIRS_1_PARAMETERS}" ${subdir}/main.cpp)
ENDFOREACH()

set(SUBDIRS_2_PARAMETERS 10 100 10)
set(SUBDIRS_2 ga1s_cp ga1s_cp_sls gt2s_ga1s_cp gt2s_ga1s_cp_sls)
FOREACH(subdir ${SUBDIRS_2})
  DCO_ADD_CASE_STUDY("${SUBDIRS_2_PARAMETERS}" ${subdir}/main.cpp)
ENDFOREACH()

## installation
set(DCO_SRC_FILES main.cpp)
set(DCO_INCLUDE_LEVEL ../../..)
if (DCO_BUILD_CASE_STUDIES)
  # used in configure below
  JOIN("${SUBDIRS_1} ${SUBDIRS_2}" " " SUBDIRS_STRING)

  # create top-level makefiles and install
  configure_file(
    ${CMAKE_SOURCE_DIR}/additionals/build_templates/${EXAMPLES_TEMPLATE}
    ${CMAKE_BINARY_DIR}/tmp_files/case_studies/diffusion/Makefile
    @ONLY
    )
  install(
    FILES ${CMAKE_BINARY_DIR}/tmp_files/case_studies/diffusion/Makefile
    DESTINATION case_studies/diffusion/
    )

  foreach (SUBDIRS SUBDIRS_1 SUBDIRS_2)
    JOIN("${${SUBDIRS}_PARAMETERS}" " " DCO_EXE_PARAMETERS)
    set(SUBDIRS ${${SUBDIRS}})
    foreach(subsubdir ${SUBDIRS})

      # install ref_results file
      FIND_REF_RESULT_FILE("${subsubdir}/" 1)
      if (${FILE_FOUND})
        set(FILE_COMPARE_COMMAND_MAKEFILE "${FILE_COMPARE_COMMAND} out ref_results")
        install(
          FILES ${REF_RES_FILE}
          DESTINATION case_studies/diffusion/${subsubdir}
          RENAME ref_results
        )
      else()
        set(FILE_COMPARE_COMMAND_MAKEFILE "")
      endif()

      # create makefile for each example and install
      configure_file(
      	${CMAKE_SOURCE_DIR}/additionals/build_templates/${SINGLE_EXAMPLE_TEMPLATE}
      	${CMAKE_BINARY_DIR}/tmp_files/case_studies/diffusion/${subsubdir}/Makefile
      	@ONLY
    	  )
      install(
      	FILES ${CMAKE_BINARY_DIR}/tmp_files/case_studies/diffusion/${subsubdir}/Makefile
      	DESTINATION case_studies/diffusion/${subsubdir}
	      )

      # Visual Studio files
      CREATE_VS_VCXPROJ_FILE(case_studies/diffusion ${subsubdir} SLN_PROJECT SLN_POST)
    endforeach()
  endforeach()

  # copy example source and header files
  install_with_copyright(DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION case_studies TARGET case_studies.diffusion)
  install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION case_studies
    FILES_MATCHING
    PATTERN "*.in"
    PATTERN "approx_results"
    PATTERN "README"
    )

  # Top level Visual Studio Files
  CREATE_VS_SLN_FILES(case_studies/diffusion)
endif()




