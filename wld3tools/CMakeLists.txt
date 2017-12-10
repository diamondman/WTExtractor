cmake_minimum_required (VERSION 3.1)
project (WLD3Tools)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #Global bin directory

include_directories(${WLD3_SOURCE_DIR})

add_executable(PWTDecode pwtdecode_cli_main.c)
target_link_libraries(PWTDecode WLD3)

add_executable(WTExtract wtextract_cli_main.c)
target_link_libraries(WTExtract WLD3)
