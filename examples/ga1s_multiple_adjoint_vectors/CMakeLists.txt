if (OPENMP_FOUND)
  DCO_ADD_TEST_CUSTOM(target_name " " main.cpp driver.cpp)
  SET_TARGET_PROPERTIES(${target_name} PROPERTIES CXX_STANDARD 11 COMPILE_FLAGS ${OpenMP_CXX_FLAGS} LINK_FLAGS ${OpenMP_CXX_FLAGS})
endif()
  
