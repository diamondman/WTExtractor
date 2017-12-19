cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

############################

project(wtengine)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

find_package(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

find_package(Java REQUIRED)
include(UseJava)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

############################

add_library( wtapi SHARED
  src/basetypes.cpp

  src/WTActor.cpp
  src/WTAudioClip3D.cpp
  src/WTAudioClip.cpp
  src/WTBitmap.cpp
  src/WTCamera.cpp
  src/WTCollisionInfo.cpp
  src/WTContainer.cpp
  src/WTDrop.cpp
  src/WTEvent.cpp
  src/WTFile.cpp
  src/WTFont.cpp
  src/WTGroup.cpp
  src/WT.cpp
  src/WTJoystick.cpp
  src/WTKeyboardPollInfo.cpp
  src/WTLight.cpp
  src/WTModel.cpp
  src/WTMousePollInfo.cpp
  src/WTObject.cpp
  src/WTOrientation3D.cpp
  src/WTPortal.cpp
  src/WTShadow.cpp
  src/WTSpout.cpp
  src/WTStage.cpp
  src/WTString3D.cpp
  src/WTSurfaceShader.cpp
  src/WTSysInfo.cpp
  src/WTVector3D.cpp
  src/WTVisualizer.cpp

  #////////src/WTEventCallback.cpp
  #///////src/WTOnLoadEvent.cpp
  )

############################

set(CMAKE_SWIG_FLAGS -package wildtangent.webdriver)
set_property(SOURCE WTEngine.i PROPERTY CPLUSPLUS ON)
set(CMAKE_SWIG_OUTDIR "${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver")
set(SWIG_MODULE_NAME "wildtangent.webdriver")
#set_property(SOURCE WTEngine.i PROPERTY CMAKE_SWIG_OUTDIR "wildtangent/webdriver")
#set_property(SOURCE WTEngine.i PROPERTY SWIG_MODULE_NAME "wildtangent.webdriver")
swig_add_module( WTEngine JAVA WTEngine.i )
#set_target_properties( WTEngine PROPERTIES CMAKE_SWIG_OUTDIR "wildtangent/webdriver")
swig_link_libraries( WTEngine wtapi )

############################

add_jar(wildtangent ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTVector3D.java)
add_dependencies( wildtangent WTEngine )

############################

add_jar(main Main.java ENTRY_POINT Main)
add_dependencies(main wildtangent)
