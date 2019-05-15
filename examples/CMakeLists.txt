include(requiredVersions.cmake)
dco_get_subdirs(. subdirs)

add_custom_target(examples)
foreach(dir ${subdirs})
  if (requiredVersion.${dir})
    if(${requiredVersion.${dir}} VERSION_GREATER "${DCO_CPP_VERSION_MAJOR}.${DCO_CPP_VERSION_MINOR}")
      MESSAGE("dco/c++ examples: Skipped. Required version: ${requiredVersion.${dir}}. Installed dco/c++ version: ${DCO_CPP_VERSION_MAJOR}.${DCO_CPP_VERSION_MINOR}. Not adding ${dir}.")
      continue()
    endif()
  endif()
  
  dco_get_test_name(name ${dir}/dummy.cpp)

  file(GLOB sources_cpp "${dir}/*.cpp")
  
  add_executable(${name} ${sources_cpp})
  target_link_libraries(${name} ${DCO_CPP_LIBRARIES})
  add_test(${name} ${name})

  add_dependencies(examples ${name})
endforeach()

