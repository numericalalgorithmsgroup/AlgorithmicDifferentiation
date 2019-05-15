# CMake generated Testfile for 
# Source directory: /home/knusulonus/git/dco_cpp_dev/examples/gbcp
# Build directory: /home/knusulonus/git/dco_cpp_dev/GIT/examples/gbcp
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(examples.gbcp "/usr/bin/cmake" "-DCMD=/home/knusulonus/git/dco_cpp_dev/GIT/examples/gbcp/examples.gbcp" "-DREF_FILE=/home/knusulonus/git/dco_cpp_dev/examples/gbcp//ref_results" "-DWIN=0" "-P" "/home/knusulonus/git/dco_cpp_dev/additionals/build_files/File_Diff_Check.cmake")
set_tests_properties(examples.gbcp PROPERTIES  WORKING_DIRECTORY "/home/knusulonus/git/dco_cpp_dev/GIT/examples/gbcp/")
