cmake_minimum_required (VERSION 3.7)

project (WLD3
  VERSION 0.0
  )

set (CMAKE_POSITION_INDEPENDENT_CODE ON)
add_library(WLD3 STATIC
  src/dataaccessors.c
  src/multifh.c
  src/wld3_extract.c
  src/pwt_decode.c
  )
target_include_directories (WLD3
  PUBLIC include
  PRIVATE src
  )
target_link_libraries (WLD3
  uuid
  mspack
  magic
  m
  )
