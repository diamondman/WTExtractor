cmake_minimum_required (VERSION 2.8.11)
project (WLD3)

# The version number.
set (WLD3_VERSION_MAJOR 0)
set (WLD3_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
#configure_file (
#  "${PROJECT_SOURCE_DIR}/WLD3Config.h.in"
#  "${PROJECT_BINARY_DIR}/WLD3Config.h"
#  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
#include_directories("${PROJECT_BINARY_DIR}")

# Add Targets
add_library(WLD3 STATIC multifh.c dataaccessors.c wld3_extract.c pwt_decode.c)
target_link_libraries(WLD3 uuid mspack magic m)

#add_executable(PWTDecode pwtdecode_cli_main.c)
#target_link_libraries(PWTDecode WLD3)

#add_executable(WTExtract wtextract_cli_main.c)
#target_link_libraries(WTExtract WLD3)
