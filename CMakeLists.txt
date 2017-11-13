cmake_minimum_required (VERSION 2.8.11)

add_subdirectory(libwld3)
add_subdirectory(wld3tools)

MESSAGE( STATUS "CMAKE_BUILD_TYPE:         " ${CMAKE_BUILD_TYPE} )
set(CMAKE_BUILD_TYPE Debug)
MESSAGE( STATUS "CMAKE_BUILD_TYPE:         " ${CMAKE_BUILD_TYPE} )

add_subdirectory(pwtviewer)
