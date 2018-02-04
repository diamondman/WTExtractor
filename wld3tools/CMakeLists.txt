cmake_minimum_required (VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (WLD3Tools)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #Global bin directory

add_executable(PWTDecode pwtdecode_cli_main.c)
target_link_libraries(PWTDecode WLD3)

add_executable(WTExtract wtextract_cli_main.c)
target_link_libraries(WTExtract WLD3)
