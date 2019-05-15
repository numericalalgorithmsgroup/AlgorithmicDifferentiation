cmake_minimum_required(VERSION 3.9)
project(dco_cpp_codes)

enable_testing()

# we're in 2019 now...
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/utils.cmake)
include(cmake/arch.cmake)
include(cmake/win_md_to_mt.cmake)

get_architecture(IS_LINUX IS_WINDOWS IS_64 IS_32)
if(IS_WINDOWS AND NOT(CMAKE_C_COMPILER_VERSION MATCHES "19.(.*)"))
  MESSAGE(FATAL_ERROR "Please use a C++11 compliant compiler, i.e. MSVC >= 2015")
endif ()

find_package(dco_cpp REQUIRED)
include_directories(${DCO_CPP_INCLUDE_DIR})
link_directories(${DCO_CPP_LIBRARY_DIR})

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
  string(APPEND CMAKE_CXX_FLAGS        " ${OpenMP_CXX_FLAGS}")
  string(APPEND CMAKE_EXE_LINKER_FLAGS " ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# auto support not required for examples / case studies
add_definitions(-DDCO_DISABLE_AUTO_WARNING -DDCO_DISABLE_AVX2_WARNING -DDCO_CPP11)

add_subdirectory(examples)
add_subdirectory(case_studies)

