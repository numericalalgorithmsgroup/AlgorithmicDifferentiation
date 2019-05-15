if (NOT ${MSVC} OR ${MSVC_VERSION} GREATER 1700)
  DCO_ADD_TEST_CUSTOM(target_name " " main.cpp driver.cpp)
  SET_TARGET_PROPERTIES(${target_name} PROPERTIES CXX_STANDARD 11)
endif()
  
