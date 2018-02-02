cmake_minimum_required (VERSION 3.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

############################

project(wtengine)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})

find_package(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})

find_package(Java REQUIRED)
include(UseJava)

find_package(Cairo)
include_directories(${Cairo_INCLUDE_DIRS})

find_package(SDL2)
include_directories(${SDL2_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${WLD3_SOURCE_DIR})

############################

add_library( wtapi SHARED
  src/basetypes.cpp
  src/InternalCallbackWrapper.cpp
  src/InternalOnLoadCallbackWrapper.hpp
  src/IUnknown.cpp

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
  )

target_link_libraries(wtapi WLD3 ${Cairo_LIBRARIES} ${SDL2_LIBRARY})

############################

set(RAW_SWIG_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/wildtangent_preprocess/webdriver/jni/")
set(PP_SWIG_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/")

set(CMAKE_SWIG_FLAGS -package wildtangent.webdriver.jni)
set_property(SOURCE WTEngine.i PROPERTY CPLUSPLUS ON)
set(CMAKE_SWIG_OUTDIR "${RAW_SWIG_GEN_DIR}")
set(SWIG_MODULE_NAME "wildtangent.webdriver.jni")
swig_add_module( WTEngine JAVA WTEngine.i )
swig_link_libraries( WTEngine wtapi )

function ( POSTPROCESS_SWIG )
  set(options OPTIONAL FAST)
  set(oneValueArgs TARGET INPREFIX OUTPREFIX INTERMEDIATE)
  set(multiValueArgs POSTPROCESS NOPROCESS)
  cmake_parse_arguments(PP_SWIG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

  #add_custom_target(build-time-make-directory ALL
  add_custom_command(
    TARGET ${PP_SWIG_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PP_SWIG_OUTPREFIX})

  add_custom_command(
    TARGET ${PP_SWIG_TARGET} POST_BUILD
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/greatreplacer.py
            --swigintermediary
            "${PP_SWIG_INPREFIX}${PP_SWIG_INTERMEDIATE}"
            "${PP_SWIG_OUTPREFIX}${PP_SWIG_INTERMEDIATE}"
    )

  foreach ( PP_FILE ${PP_SWIG_POSTPROCESS} )
    add_custom_command(
      TARGET ${PP_SWIG_TARGET} POST_BUILD
      COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/greatreplacer.py
              "${PP_SWIG_INPREFIX}${PP_FILE}"
              "${PP_SWIG_OUTPREFIX}${PP_FILE}"
      )
  endforeach( PP_FILE ${PP_SWIG_POSTPROCESS} )

  foreach ( PP_FILE ${PP_SWIG_NOPROCESS} )
    add_custom_command(
      TARGET ${PP_SWIG_TARGET} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
              "${PP_SWIG_INPREFIX}${PP_FILE}"
              "${PP_SWIG_OUTPREFIX}${PP_FILE}")
  endforeach( PP_FILE ${PP_SWIG_POSTPROCESS} )
endfunction( POSTPROCESS_SWIG )

postprocess_swig(TARGET WTEngine
  INPREFIX "${RAW_SWIG_GEN_DIR}"
  OUTPREFIX "${PP_SWIG_GEN_DIR}"
  INTERMEDIATE WTEngineJNI.java
  NOPROCESS
    InternalCallbackWrapper.java
    InternalOnLoadCallbackWrapper.java
    IUnknown.java
    WTEngine.java
  POSTPROCESS
    WTActor.java
    WTAudioClip3D.java
    WTAudioClip.java
    WTBitmap.java
    WTCamera.java
    WTCollisionInfo.java
    WTContainer.java
    WTDrop.java
    WTEvent.java
    WTFile.java
    WTFont.java
    WTGroup.java
    WT.java
    WTJoystick.java
    WTKeyboardPollInfo.java
    WTLight.java
    WTModel.java
    WTMousePollInfo.java
    WTObject.java
    WTOrientation3D.java
    WTPortal.java
    WTShadow.java
    WTSpout.java
    WTStage.java
    WTString3D.java
    WTSurfaceShader.java
    WTSysInfo.java
    WTVector3D.java
    WTVisualizer.java
)

############################

add_jar(wildtangent
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/InternalCallbackWrapper.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/InternalOnLoadCallbackWrapper.java

  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTActor.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTAudioClip3D.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTAudioClip.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTBitmap.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTCamera.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTCollisionInfo.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTContainer.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTDrop.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTEngine.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTEngineJNI.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTEvent.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTFile.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTFont.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTGroup.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WT.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTJoystick.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTKeyboardPollInfo.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTLight.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTModel.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTMousePollInfo.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTObject.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTOrientation3D.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTPortal.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTShadow.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTSpout.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTStage.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTString3D.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTSurfaceShader.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTSysInfo.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTVector3D.java
  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni/WTVisualizer.java

  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTActor.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTAudioClip3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTAudioClip.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTBitmap.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTCamera.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTCollisionInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTContainer.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTDrop.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTEventCallback.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTEventJoystickCallback.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTFile.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTFont.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTGroup.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WT.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTJoystick.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTKeyboardPollInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTLight.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTModel.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTMousePollInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTObject.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTOnLoadEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTOrientation3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTPortal.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTShadow.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTSpout.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTStage.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTString3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTSurfaceShader.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTSysInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTVector3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTVisualizer.java

  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/InternalExceptionEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/InternalKeyboardEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/InternalMouseEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/InternalRenderEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/InternalLoadEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTActor.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTAudioClip3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTAudioClip.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTBitmap.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTCamera.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTCollisionInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTContainer.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTDrop.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTEvent.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTFile.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTFont.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTGroup.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WT.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTJoystick.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTKeyboardPollInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTLight.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTModel.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTMousePollInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTObject.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTOrientation3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTPortal.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTShadow.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTSpout.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTStage.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTString3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTSurfaceShader.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTSysInfo.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTVector3D.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/impl/WTVisualizer.java

  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/WTConstants.java
  ${CMAKE_CURRENT_SOURCE_DIR}/javasrc/wildtangent/webdriver/wt3dLib.java
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

  ${RTSRC}/netscape/javascript/JSObject.java
  )

############################

set(CMAKE_JAVA_INCLUDE_PATH ${CMAKE_CURRENT_BINARY_DIR}/wildtangent.jar:${CMAKE_CURRENT_BINARY_DIR}/rt.jar)
add_jar(WTPlayerMain WTPlayerMain.java)# ENTRY_POINT Main)
add_dependencies(WTPlayerMain wildtangent rt)

############################

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/templates/run.sh.template
  ${CMAKE_CURRENT_BINARY_DIR}/run.sh
  COPYONLY)
