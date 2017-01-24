cmake_minimum_required (VERSION 2.8.11)
project (WLD3Tools)

#include_directories()

include_directories(${WLD3_SOURCE_DIR})

add_executable(PWTDecode pwtdecode_cli_main.c)
target_link_libraries(PWTDecode WLD3)

add_executable(WTExtract wtextract_cli_main.c)
target_link_libraries(WTExtract WLD3)

#target_include_directories(PWTDecode PUBLIC WLD3)
#target_include_directories(WTExtract PUBLIC WLD3)
