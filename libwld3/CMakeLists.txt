cmake_minimum_required (VERSION 3.1)
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

# Add Targets
add_library(WLD3 STATIC dataaccessors.c multifh.c wld3_extract.c pwt_decode.c)
target_link_libraries(WLD3 uuid mspack magic m)
