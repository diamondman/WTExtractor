cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (pwtviewer)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) #Global bin directory
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")

#----------------------------------------------------------------------------------------

# On Windows it's a regular copy.
# On Apple it does nothing
# On Linux, it copies both libOgreMain.so.2.1 and its symbolic link libOgreMain.so
function( copyWithSymLink SRC DST )
  if( NOT APPLE )
    if( UNIX )
      get_filename_component( RESOLVED_LIB_PATH ${SRC} REALPATH )
      file( COPY ${RESOLVED_LIB_PATH} DESTINATION ${DST} )
    endif()
    file( COPY ${SRC} DESTINATION ${DST} )
  endif()
endfunction()

#OGRE
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(OGRE REQUIRED)
include_directories( ${OGRE_INCLUDE_DIRS} )

#QT5
find_package(Qt5Widgets)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#libwld3
#include_directories(${WLD3_INCLUDE_DIRS})
include_directories(${WLD3_SOURCE_DIR})

#DEBUG STUFF
MESSAGE( STATUS "CMAKE_MODULE_PATH:                   " ${CMAKE_MODULE_PATH} )
MESSAGE( STATUS "CMAKE_CURRENT_LIST_DIR:              " ${CMAKE_CURRENT_LIST_DIR} )
MESSAGE( STATUS "OGRE_LIBRARIES:                      " ${OGRE_LIBRARIES} )
MESSAGE( STATUS "OGRE_INCLUDE_DIRS:                   " ${OGRE_INCLUDE_DIRS} )
MESSAGE( STATUS "OPENGL FOUND:                        " ${OGRE_RenderSystem_GL3Plus_FOUND} )
MESSAGE( STATUS "OGRE_RenderSystem_GL3Plus_LIBRARIES: " ${OGRE_RenderSystem_GL3Plus_LIBRARIES} )
MESSAGE( STATUS "OPENGL_LIBRARIES:                    " ${OPENGL_LIBRARIES} )
MESSAGE( STATUS "OPENGL PLUGIN:                       " ${OGRE_RenderSystem_GL3Plus_LIBRARY_DBG} )

#EXECUTABLE
#set(CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
add_executable(pwtviewer
  main.cpp MainWindow.cpp
  PWTModelFrame.cpp FrameTreeItem.cpp FrameTreeModel.cpp ModelFrameTreeView.cpp
  resource.qrc)
target_link_libraries(pwtviewer Qt5::Widgets WLD3 ${OGRE_LIBRARIES} OgreHlmsPbs OgreHlmsUnlit)

#copyWithSymLink(${OGRE_RenderSystem_GL3Plus_LIBRARY_DBG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#${CMAKE_CURRENT_BINARY_DIR}/bin)
copyWithSymLink(${OGRE_RenderSystem_GL3Plus_LIBRARY_REL} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#${CMAKE_CURRENT_BINARY_DIR}/bin)
file( COPY ${PROJECT_SOURCE_DIR}/Hlms DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
