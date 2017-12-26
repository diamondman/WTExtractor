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
//#include "WTEventCallback.hpp"
#include "WTEvent.hpp"
#include "WTFile.hpp"
#include "WTFont.hpp"
#include "WT.hpp"
#include "WTJoystick.hpp"
#include "WTKeyboardPollInfo.hpp"
#include "WTLight.hpp"
#include "WTModel.hpp"
#include "WTMousePollInfo.hpp"
//#include "WTOnLoadEvent.hpp"
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

//Override incredibly poor defaults for java primitives (Default unsigned char = short)
%typemap(jni)    unsigned char,      const unsigned char &      "jbyte"
%typemap(jtype)  unsigned char,      const unsigned char &      "byte"
%typemap(jstype) unsigned char,      const unsigned char &      "byte"

%include <arrays_java.i>
JAVA_ARRAYS_DECL(uint8_t, jbyte, byte, UInt8) /* uint8_t[] */
JAVA_ARRAYS_IMPL(uint8_t, jbyte, Byte, UInt8) /* uint8_t[] */
//%define JAVA_ARRAYS_TYPEMAPS(CTYPE, JTYPE, JNITYPE, JFUNCNAME, JNIDESC
JAVA_ARRAYS_TYPEMAPS(uint8_t, byte, jbyte, UInt8, "[S") /* uint8_t[ANY] */

//Generic Object wrapper.
%typemap(jni) VARIANT "jobject"
%typemap(jtype) VARIANT "Object"
%typemap(jstype) VARIANT "Object"

%typemap(javain) VARIANT "$javainput"
%typemap(javaout) VARIANT {
  return $jnicall;
}

%typemap(in) VARIANT {
  $1 = std::make_shared<jobject_wrap>(jenv, $input);
}
%typemap(out) VARIANT {
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
//%include "WTEventCallback.hpp"
%include "WTEvent.hpp"
%include "WTFile.hpp"
%include "WTFont.hpp"
%include "WT.hpp"
%include "WTJoystick.hpp"
%include "WTKeyboardPollInfo.hpp"
%include "WTLight.hpp"
%include "WTModel.hpp"
%include "WTMousePollInfo.hpp"
//%include "WTOnLoadEvent.hpp"
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
