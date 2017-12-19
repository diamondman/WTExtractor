%module WTEngine
%{
#include "basetypes.hpp"

/* Includes the header in the wrapper code */
#include "WTObject.hpp"
#include "WTContainer.hpp"
#include "WTGroup.hpp"
#include "WTActor.hpp"
#include "WTAudioClip3D.hpp"
#include "WTAudioClip.hpp"
#include "WTBitmap.hpp"
#include "WTCamera.hpp"
#include "WTCollisionInfo.hpp"
#include "WTDrop.hpp"
#include "WTEventCallback.hpp"
#include "WTEvent.hpp"
#include "WTFile.hpp"
#include "WTFont.hpp"
#include "WT.hpp"
#include "WTJoystick.hpp"
#include "WTKeyboardPollInfo.hpp"
#include "WTLight.hpp"
#include "WTModel.hpp"
#include "WTMousePollInfo.hpp"
#include "WTOnLoadEvent.hpp"
#include "WTOrientation3D.hpp"
#include "WTPortal.hpp"
#include "WTShadow.hpp"
#include "WTSpout.hpp"
#include "WTStage.hpp"
#include "WTString3D.hpp"
#include "WTSurfaceShader.hpp"
#include "WTSysInfo.hpp"
#include "WTVector3D.hpp"
#include "WTVisualizer.hpp"

#include <stdint.h>
%}

%typemap(jni) VARIANT "jobject"
%typemap(jtype) VARIANT "Object"
%typemap(jstype) VARIANT "Object"

%typemap(javain) VARIANT "$javainput"
%typemap(javaout) VARIANT {
  return $jnicall;
}

%typemap(in) VARIANT
 {
   $1 = std::make_shared<jobject_wrap>(jenv, $input);
 }
%typemap(out) VARIANT
 {
   $result = $1->getObject();
 }

///////////////////////////////////////////////


/* Parse the header file to generate wrappers */
%include "WTObject.hpp"
%include "WTContainer.hpp"
%include "WTGroup.hpp"
%include "WTActor.hpp"
%include "WTAudioClip3D.hpp"
%include "WTAudioClip.hpp"
%include "WTBitmap.hpp"
%include "WTCamera.hpp"
%include "WTCollisionInfo.hpp"
%include "WTDrop.hpp"
%include "WTEventCallback.hpp"
%include "WTEvent.hpp"
%include "WTFile.hpp"
%include "WTFont.hpp"
%include "WT.hpp"
%include "WTJoystick.hpp"
%include "WTKeyboardPollInfo.hpp"
%include "WTLight.hpp"
%include "WTModel.hpp"
%include "WTMousePollInfo.hpp"
%include "WTOnLoadEvent.hpp"
%include "WTOrientation3D.hpp"
%include "WTPortal.hpp"
%include "WTShadow.hpp"
%include "WTSpout.hpp"
%include "WTStage.hpp"
%include "WTString3D.hpp"
%include "WTSurfaceShader.hpp"
%include "WTSysInfo.hpp"
%include "WTVector3D.hpp"
%include "WTVisualizer.hpp"
