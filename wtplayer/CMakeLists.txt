cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

############################

project(wtengine)

find_package(JNI REQUIRED)

find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

find_package(Java REQUIRED)
include(UseJava)

find_package(Cairo)

find_package(SDL2 REQUIRED)

find_package(PNG REQUIRED)

############################

add_library(wtapi SHARED
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

target_include_directories(wtapi
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  PRIVATE
    ${JNI_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
    ${Cairo_INCLUDE_DIRS}
  )

target_link_libraries(wtapi
  PRIVATE
    WLD3
    ${Cairo_LIBRARIES}
    ${SDL2_LIBRARY}
    ${PNG_LIBRARIES}
  )

############################

set(RAW_SWIG_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/swig_generated_raw")
set(PP_SWIG_GEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/wildtangent/webdriver/jni")

set(SWIG_MODULE_NAME "wildtangent.webdriver.jni")
set(CMAKE_SWIG_FLAGS -package ${SWIG_MODULE_NAME})
set(CMAKE_SWIG_OUTDIR "${RAW_SWIG_GEN_DIR}")

set_property(SOURCE WTEngine.i PROPERTY CPLUSPLUS ON)

swig_add_library(WTEngine
  TYPE SHARED
  LANGUAGE JAVA
  SOURCES WTEngine.i
  )
set(WTEngine_GENERATED_SOURCES ${swig_generated_sources})
message(STATUS "WUT ${swig_custom_output} -- ${swig_custom_products}")

target_include_directories(WTEngine
  PRIVATE
    ${JNI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

swig_link_libraries( WTEngine PRIVATE wtapi )

message(STATUS "********************* ${WTEngine_GENERATED_SOURCES}")

#Trying to make the Generated Java files be a target
#add_custom_command(
#  OUTPUT
#    #${RAW_SWIG_GEN_DIR}/WTEngineJNI.java
#
#    #${RAW_SWIG_GEN_DIR}/WTEngine.java
#    ${RAW_SWIG_GEN_DIR}/InternalCallbackWrapper.java
#    ${RAW_SWIG_GEN_DIR}/InternalOnLoadCallbackWrapper.java
#    ${RAW_SWIG_GEN_DIR}/IUnknown.java
#
#    ${RAW_SWIG_GEN_DIR}/WTActor.java
#    ${RAW_SWIG_GEN_DIR}/WTAudioClip3D.java
#    ${RAW_SWIG_GEN_DIR}/WTAudioClip.java
#    ${RAW_SWIG_GEN_DIR}/WTBitmap.java
#    ${RAW_SWIG_GEN_DIR}/WTCamera.java
#    ${RAW_SWIG_GEN_DIR}/WTCollisionInfo.java
#    ${RAW_SWIG_GEN_DIR}/WTContainer.java
#    ${RAW_SWIG_GEN_DIR}/WTDrop.java
#    ${RAW_SWIG_GEN_DIR}/WTEvent.java
#    ${RAW_SWIG_GEN_DIR}/WTFile.java
#    ${RAW_SWIG_GEN_DIR}/WTFont.java
#    ${RAW_SWIG_GEN_DIR}/WTGroup.java
#    ${RAW_SWIG_GEN_DIR}/WT.java
#    ${RAW_SWIG_GEN_DIR}/WTJoystick.java
#    ${RAW_SWIG_GEN_DIR}/WTKeyboardPollInfo.java
#    ${RAW_SWIG_GEN_DIR}/WTLight.java
#    ${RAW_SWIG_GEN_DIR}/WTModel.java
#    ${RAW_SWIG_GEN_DIR}/WTMousePollInfo.java
#    ${RAW_SWIG_GEN_DIR}/WTObject.java
#    ${RAW_SWIG_GEN_DIR}/WTOrientation3D.java
#    ${RAW_SWIG_GEN_DIR}/WTPortal.java
#    ${RAW_SWIG_GEN_DIR}/WTShadow.java
#    ${RAW_SWIG_GEN_DIR}/WTSpout.java
#    ${RAW_SWIG_GEN_DIR}/WTStage.java
#    ${RAW_SWIG_GEN_DIR}/WTString3D.java
#    ${RAW_SWIG_GEN_DIR}/WTSurfaceShader.java
#    ${RAW_SWIG_GEN_DIR}/WTSysInfo.java
#    ${RAW_SWIG_GEN_DIR}/WTVector3D.java
#    ${RAW_SWIG_GEN_DIR}/WTVisualizer.java
#
#  DEPENDS
#    ${WTEngine_GENERATED_SOURCES}
#
#  COMMENT "Mocking the generation of the swig files"
#  )
#
set(FILENAME "WTEngineJAVA_wrap.stamp")#"WTEngineJAVA_wrap.cxx")

get_source_file_property(DERP_IS_GEN "${RAW_SWIG_GEN_DIR}/${FILENAME}" GENERATED)
message(STATUS "&&&&&&&&&&&&&&& ${RAW_SWIG_GEN_DIR}/${FILENAME} ${DERP_IS_GEN}")

set_property(SOURCE "${RAW_SWIG_GEN_DIR}/${FILENAME}" PROPERTY GENERATED 1)

get_source_file_property(DERP_IS_GEN "${RAW_SWIG_GEN_DIR}/${FILENAME}" GENERATED)
message(STATUS "&&&&&&&&&&&&&&& ${RAW_SWIG_GEN_DIR}/${FILENAME} ${DERP_IS_GEN}")
#
#  foreach ( ABC_FILE ${WTEngine_GENERATED_SOURCES} )
#    get_source_file_property(DERP_IS_GEN "${ABC_FILE}" GENERATED)
#    message(STATUS "&&&&&&&&&&&&&&& ${ABC_FILE} = ${DERP_IS_GEN}")
#    #set_property(SOURCE "${ABC_FILE}" PROPERTY GENERATED 0)
#  endforeach( ABC_FILE ${WTEngine_GENERATED_SOURCES} )
#
#
# file(MAKE_DIRECTORY ${PP_SWIG_GEN_DIR})

#
add_custom_target(DERPIDERP ALL DEPENDS "${PP_SWIG_GEN_DIR}/WTActor.java")

add_custom_command(
  OUTPUT ${PP_SWIG_GEN_DIR}/WTActor.java
  COMMAND ${CMAKE_COMMAND} -E copy
          "${RAW_SWIG_GEN_DIR}/WTActor.java"
          "${PP_SWIG_GEN_DIR}/WTActor.java"
  DEPENDS "${RAW_SWIG_GEN_DIR}/WTEngineJAVA_wrap.stamp"
          #gen_WTEngine_WTEngineJAVA_wrap #"${RAW_SWIG_GEN_DIR}/WTActor.java"
          #${WTEngine_GENERATED_SOURCES}
  COMMENT "DOING THE THINNNNNGGGGGGGGGGGGGGGGGGGGGGG"
  )
set_property(SOURCE "${PP_SWIG_GEN_DIR}/WTActor.java"
  PROPERTY GENERATED 1)


#add_dependencies(DERPIDERP gen_WTEngine_WTEngineJAVA_wrap)
#"${PP_SWIG_GEN_DIR}/WTActor.java")
#${RAW_SWIG_GEN_DIR}/WTActor.java)


#function ( POSTPROCESS_SWIG )
#  set(options)
#  set(oneValueArgs TARGET INPREFIX OUTPREFIX INTERMEDIATE)
#  set(multiValueArgs POSTPROCESS NOPROCESS)
#  cmake_parse_arguments(POSTPROCESS_SWIG
#    "${options}" "${oneValueArgs}" "${multiValueArgs}"
#    ${ARGN}
#    )
#
#  add_custom_command(
#    TARGET ${POSTPROCESS_SWIG_TARGET} POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E make_directory ${POSTPROCESS_SWIG_OUTPREFIX}
#    )
#
#  ###
#  add_custom_command(
#    TARGET ${POSTPROCESS_SWIG_TARGET} POST_BUILD
#    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/greatreplacer.py
#            --swigintermediary
#            "${POSTPROCESS_SWIG_INPREFIX}${POSTPROCESS_SWIG_INTERMEDIATE}"
#            "${POSTPROCESS_SWIG_OUTPREFIX}${POSTPROCESS_SWIG_INTERMEDIATE}"
#    COMMENT "PostProcessing Swig Generated File ${POSTPROCESS_SWIG_INTERMEDIATE}"
#    )
#  get_source_file_property(swig_source_file_generated
#    "${POSTPROCESS_SWIG_INPREFIX}${POSTPROCESS_SWIG_INTERMEDIATE}" GENERATED)
#  message(STATUS "Generated Status of INFILE ${POSTPROCESS_SWIG_INTERMEDIATE} = "
#    "${swig_source_file_generated}")
#
#  set_property(SOURCE "${POSTPROCESS_SWIG_OUTPREFIX}${POSTPROCESS_SWIG_INTERMEDIATE}"
#    PROPERTY GENERATED 1)
#
#  ###
#  foreach ( PP_FILE ${POSTPROCESS_SWIG_POSTPROCESS} )
#    add_custom_command(
#      TARGET ${POSTPROCESS_SWIG_TARGET} POST_BUILD
#      COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/greatreplacer.py
#              "${POSTPROCESS_SWIG_INPREFIX}${PP_FILE}"
#              "${POSTPROCESS_SWIG_OUTPREFIX}${PP_FILE}"
#      )
#    set_property(SOURCE ${POSTPROCESS_SWIG_OUTPREFIX}/${PP_FILE}
#      PROPERTY GENERATED 1)
#  endforeach( PP_FILE ${POSTPROCESS_SWIG_POSTPROCESS} )
#
#  ###
#  foreach ( PP_FILE ${POSTPROCESS_SWIG_NOPROCESS} )
#    add_custom_command(
#      TARGET ${POSTPROCESS_SWIG_TARGET} POST_BUILD
#      COMMAND ${CMAKE_COMMAND} -E copy
#              "${POSTPROCESS_SWIG_INPREFIX}/${PP_FILE}"
#              "${POSTPROCESS_SWIG_OUTPREFIX}/${PP_FILE}"
#      )
#    set_property(SOURCE ${POSTPROCESS_SWIG_OUTPREFIX}/${PP_FILE}
#      PROPERTY GENERATED 1)
#  endforeach( PP_FILE ${POSTPROCESS_SWIG_POSTPROCESS} )
#endfunction( POSTPROCESS_SWIG )

#postprocess_swig(TARGET WTEngine
#  INPREFIX "${RAW_SWIG_GEN_DIR}/"
#  OUTPREFIX "${PP_SWIG_GEN_DIR}/"
#  INTERMEDIATE WTEngineJNI.java
#  NOPROCESS
#    InternalCallbackWrapper.java
#    InternalOnLoadCallbackWrapper.java
#    IUnknown.java
#    WTEngine.java
#  POSTPROCESS
#    WTActor.java
#    WTAudioClip3D.java
#    WTAudioClip.java
#    WTBitmap.java
#    WTCamera.java
#    WTCollisionInfo.java
#    WTContainer.java
#    WTDrop.java
#    WTEvent.java
#    WTFile.java
#    WTFont.java
#    WTGroup.java
#    WT.java
#    WTJoystick.java
#    WTKeyboardPollInfo.java
#    WTLight.java
#    WTModel.java
#    WTMousePollInfo.java
#    WTObject.java
#    WTOrientation3D.java
#    WTPortal.java
#    WTShadow.java
#    WTSpout.java
#    WTStage.java
#    WTString3D.java
#    WTSurfaceShader.java
#    WTSysInfo.java
#    WTVector3D.java
#    WTVisualizer.java
#)

############################

#set(JAVASRC "${CMAKE_CURRENT_SOURCE_DIR}/javasrc")
#
#add_jar(wildtangent
#  ${PP_SWIG_GEN_DIR}/InternalCallbackWrapper.java
#  ${PP_SWIG_GEN_DIR}/InternalOnLoadCallbackWrapper.java
#
#  ${PP_SWIG_GEN_DIR}/WTActor.java
#  ${PP_SWIG_GEN_DIR}/WTAudioClip3D.java
#  ${PP_SWIG_GEN_DIR}/WTAudioClip.java
#  ${PP_SWIG_GEN_DIR}/WTBitmap.java
#  ${PP_SWIG_GEN_DIR}/WTCamera.java
#  ${PP_SWIG_GEN_DIR}/WTCollisionInfo.java
#  ${PP_SWIG_GEN_DIR}/WTContainer.java
#  ${PP_SWIG_GEN_DIR}/WTDrop.java
#  ${PP_SWIG_GEN_DIR}/WTEngine.java
#  ${PP_SWIG_GEN_DIR}/WTEngineJNI.java
#  ${PP_SWIG_GEN_DIR}/WTEvent.java
#  ${PP_SWIG_GEN_DIR}/WTFile.java
#  ${PP_SWIG_GEN_DIR}/WTFont.java
#  ${PP_SWIG_GEN_DIR}/WTGroup.java
#  ${PP_SWIG_GEN_DIR}/WT.java
#  ${PP_SWIG_GEN_DIR}/WTJoystick.java
#  ${PP_SWIG_GEN_DIR}/WTKeyboardPollInfo.java
#  ${PP_SWIG_GEN_DIR}/WTLight.java
#  ${PP_SWIG_GEN_DIR}/WTModel.java
#  ${PP_SWIG_GEN_DIR}/WTMousePollInfo.java
#  ${PP_SWIG_GEN_DIR}/WTObject.java
#  ${PP_SWIG_GEN_DIR}/WTOrientation3D.java
#  ${PP_SWIG_GEN_DIR}/WTPortal.java
#  ${PP_SWIG_GEN_DIR}/WTShadow.java
#  ${PP_SWIG_GEN_DIR}/WTSpout.java
#  ${PP_SWIG_GEN_DIR}/WTStage.java
#  ${PP_SWIG_GEN_DIR}/WTString3D.java
#  ${PP_SWIG_GEN_DIR}/WTSurfaceShader.java
#  ${PP_SWIG_GEN_DIR}/WTSysInfo.java
#  ${PP_SWIG_GEN_DIR}/WTVector3D.java
#  ${PP_SWIG_GEN_DIR}/WTVisualizer.java
#
#  ${JAVASRC}/wildtangent/webdriver/WTActor.java
#  ${JAVASRC}/wildtangent/webdriver/WTAudioClip3D.java
#  ${JAVASRC}/wildtangent/webdriver/WTAudioClip.java
#  ${JAVASRC}/wildtangent/webdriver/WTBitmap.java
#  ${JAVASRC}/wildtangent/webdriver/WTCamera.java
#  ${JAVASRC}/wildtangent/webdriver/WTCollisionInfo.java
#  ${JAVASRC}/wildtangent/webdriver/WTContainer.java
#  ${JAVASRC}/wildtangent/webdriver/WTDrop.java
#  ${JAVASRC}/wildtangent/webdriver/WTEventCallback.java
#  ${JAVASRC}/wildtangent/webdriver/WTEventJoystickCallback.java
#  ${JAVASRC}/wildtangent/webdriver/WTEvent.java
#  ${JAVASRC}/wildtangent/webdriver/WTFile.java
#  ${JAVASRC}/wildtangent/webdriver/WTFont.java
#  ${JAVASRC}/wildtangent/webdriver/WTGroup.java
#  ${JAVASRC}/wildtangent/webdriver/WT.java
#  ${JAVASRC}/wildtangent/webdriver/WTJoystick.java
#  ${JAVASRC}/wildtangent/webdriver/WTKeyboardPollInfo.java
#  ${JAVASRC}/wildtangent/webdriver/WTLight.java
#  ${JAVASRC}/wildtangent/webdriver/WTModel.java
#  ${JAVASRC}/wildtangent/webdriver/WTMousePollInfo.java
#  ${JAVASRC}/wildtangent/webdriver/WTObject.java
#  ${JAVASRC}/wildtangent/webdriver/WTOnLoadEvent.java
#  ${JAVASRC}/wildtangent/webdriver/WTOrientation3D.java
#  ${JAVASRC}/wildtangent/webdriver/WTPortal.java
#  ${JAVASRC}/wildtangent/webdriver/WTShadow.java
#  ${JAVASRC}/wildtangent/webdriver/WTSpout.java
#  ${JAVASRC}/wildtangent/webdriver/WTStage.java
#  ${JAVASRC}/wildtangent/webdriver/WTString3D.java
#  ${JAVASRC}/wildtangent/webdriver/WTSurfaceShader.java
#  ${JAVASRC}/wildtangent/webdriver/WTSysInfo.java
#  ${JAVASRC}/wildtangent/webdriver/WTVector3D.java
#  ${JAVASRC}/wildtangent/webdriver/WTVisualizer.java
#
#  ${JAVASRC}/wildtangent/webdriver/impl/InternalExceptionEvent.java
#  ${JAVASRC}/wildtangent/webdriver/impl/InternalKeyboardEvent.java
#  ${JAVASRC}/wildtangent/webdriver/impl/InternalMouseEvent.java
#  ${JAVASRC}/wildtangent/webdriver/impl/InternalRenderEvent.java
#  ${JAVASRC}/wildtangent/webdriver/impl/InternalLoadEvent.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTActor.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTAudioClip3D.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTAudioClip.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTBitmap.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTCamera.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTCollisionInfo.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTContainer.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTDrop.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTEvent.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTFile.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTFont.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTGroup.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WT.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTJoystick.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTKeyboardPollInfo.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTLight.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTModel.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTMousePollInfo.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTObject.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTOrientation3D.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTPortal.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTShadow.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTSpout.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTStage.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTString3D.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTSurfaceShader.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTSysInfo.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTVector3D.java
#  ${JAVASRC}/wildtangent/webdriver/impl/WTVisualizer.java
#
#  ${JAVASRC}/wildtangent/webdriver/WTConstants.java
#  ${JAVASRC}/wildtangent/webdriver/wt3dLib.java
#  )
#add_dependencies( wildtangent WTEngine )

############################

#set(RTSRC ${JAVASRC})
#add_jar(rt
#  ${RTSRC}/com/ms/com/_Guid.java ${RTSRC}/com/ms/com/IUnknown.java
#  ${RTSRC}/com/ms/com/NoAutoScripting.java
#  ${RTSRC}/com/ms/com/SafeArray.java ${RTSRC}/com/ms/com/Variant.java
#
#  ${RTSRC}/com/ms/security/PermissionDataSet.java
#  ${RTSRC}/com/ms/security/PermissionID.java
#  ${RTSRC}/com/ms/security/PermissionSet.java
#  ${RTSRC}/com/ms/security/PolicyEngine.java
#  ${RTSRC}/com/ms/security/SecurityClassLoader.java
#
#  ${RTSRC}/com/ms/wfc/util/Debug.java
#
#  ${RTSRC}/java/applet/Applet.java
#
#  ${RTSRC}/netscape/javascript/JSObject.java
#  )

############################

#set(CMAKE_JAVA_INCLUDE_PATH
#  ${CMAKE_CURRENT_BINARY_DIR}/wildtangent.jar:${CMAKE_CURRENT_BINARY_DIR}/rt.jar)
#add_jar(WTPlayerMain WTPlayerMain.java)# ENTRY_POINT Main)
#add_dependencies(WTPlayerMain wildtangent rt)

############################

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/templates/run.sh.template
  ${CMAKE_CURRENT_BINARY_DIR}/run.sh
  COPYONLY
  )
