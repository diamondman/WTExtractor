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

add_jar(wildtangent
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTActor.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTAudioClip3D.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTAudioClip.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTBitmap.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTCamera.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTCollisionInfo.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTContainer.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTDrop.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTEngine.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTEngineJNI.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTEventCallback.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTEvent.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTFile.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTFont.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTGroup.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WT.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTJoystick.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTKeyboardPollInfo.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTLight.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTModel.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTMousePollInfo.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTObject.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTOnLoadEvent.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTOrientation3D.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTPortal.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTShadow.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTSpout.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTStage.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTString3D.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTSurfaceShader.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTSysInfo.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTVector3D.java
  ${CMAKE_BINARY_DIR}/wildtangent/webdriver/WTVisualizer.java

  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTConstants.java
  )
add_dependencies( wildtangent WTEngine )

############################

set(RTSRC ${CMAKE_CURRENT_SOURCE_DIR}/javasrc)
add_jar(rt
  ${RTSRC}/com/ms/com/_Guid.java ${RTSRC}/com/ms/com/IUnknown.java
  ${RTSRC}/com/ms/com/NoAutoScripting.java
  ${RTSRC}/com/ms/com/SafeArray.java ${RTSRC}/com/ms/com/Variant.java

  ${RTSRC}/com/ms/security/PermissionDataSet.java
  ${RTSRC}/com/ms/security/PermissionID.java
  ${RTSRC}/com/ms/security/PermissionSet.java
  ${RTSRC}/com/ms/security/PolicyEngine.java
  ${RTSRC}/com/ms/security/SecurityClassLoader.java

  ${RTSRC}/com/ms/wfc/util/Debug.java

  ${RTSRC}/java/applet/Applet.java

  ${RTSRC}/netscape/javascript/JSObject
  )

############################

set(CMAKE_JAVA_INCLUDE_PATH ${CMAKE_BINARY_DIR}/wildtangent.jar:${CMAKE_BINARY_DIR}/rt.jar)
add_jar(Main Main.java)# ENTRY_POINT Main)
add_dependencies(Main wildtangent rt)

############################

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/templates/run.sh.template
  ${CMAKE_CURRENT_BINARY_DIR}/run.sh
  COPYONLY)
