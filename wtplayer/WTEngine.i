%module(directors="1") WTEngine
%{
#include "basetypes.hpp"
#include "InternalCallbackWrapper.hpp"
#include "InternalOnLoadCallbackWrapper.hpp"

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

%feature("director") InternalCallbackWrapper;
%feature("director") InternalOnLoadCallbackWrapper;

%ignore IUnknown::AddRef;
%ignore IUnknown::Release;
%ignore IUnknown::GetRefCount;
%feature("ref")   IUnknown "$this->AddRef();"
%feature("unref") IUnknown "$this->Release();"
%include "IUnknown.hpp"

%newobject InternalCallbackWrapper;
%include "InternalCallbackWrapper.hpp"
%include "InternalOnLoadCallbackWrapper.hpp"

%ignore WTObject::WTObject;
%include "WTObject.hpp"

%ignore WTContainer::WTContainer;
%include "WTContainer.hpp"

%ignore WTGroup::WTGroup;
%include "WTGroup.hpp"

%ignore WTActor::WTActor;
%include "WTActor.hpp"

%ignore WTAudioClip3D::WTAudioClip3D;
%include "WTAudioClip3D.hpp"

%ignore WTAudioClip::WTAudioClip;
%include "WTAudioClip.hpp"

%ignore WTBitmap::WTBitmap;
%include "WTBitmap.hpp"

%ignore WTCamera::WTCamera;
%include "WTCamera.hpp"

%ignore WTCollisionInfo::WTCollisionInfo;
%include "WTCollisionInfo.hpp"

%ignore WTDrop::WTDrop;
%include "WTDrop.hpp"

//The WTEvent constructor is necessary, for now at least.
%include "WTEvent.hpp"

%ignore WTFile::WTFile;
%include "WTFile.hpp"

%ignore WTFont::WTFont;
%include "WTFont.hpp"

%newobject createStage;
%newobject createBox;
%newobject createStage;
%newobject createModel;
%newobject createContainer;
%newobject createLight;
%newobject createGroup;
%newobject createBlankBitmap;
%newobject createBitmap;
%newobject createAudioClip;
%newobject createAudioVisualizer;
%newobject createLine;
%newobject createCone;
%newobject createCylinder;
%newobject createPlane;
%newobject createPatch;
%newobject createSphere;
%newobject createJoystick;
%newobject createGroupFromFile;
%newobject createActor;
%newobject createSurfaceShader;
%newobject createFont;
%newobject createAudioClip3D;
%newobject createSpout;
%newobject createPortal;
%newobject createMesh;
%newobject createBlankMesh;
%newobject createString3D;
%newobject createShadow;
%include "WT.hpp"

%ignore WTJoystick::WTJoystick;
%include "WTJoystick.hpp"

%ignore WTKeyboardPollInfo::WTKeyboardPollInfo;
%include "WTKeyboardPollInfo.hpp"

%ignore WTLight::WTLight;
%include "WTLight.hpp"

%ignore WTModel::WTModel;
%include "WTModel.hpp"

%ignore WTMousePollInfo::WTMousePollInfo;
%include "WTMousePollInfo.hpp"

%ignore WTOrientation3D::WTOrientation3D;
%include "WTOrientation3D.hpp"

%ignore WTPortal::WTPortal;
%include "WTPortal.hpp"

%ignore WTShadow::WTShadow;
%include "WTShadow.hpp"

%ignore WTSpout::WTSpout;
%include "WTSpout.hpp"

%ignore WTStage::WTStage;
%include "WTStage.hpp"

%ignore WTString3D::WTString3D;
%include "WTString3D.hpp"

%ignore WTSurfaceShader::WTSurfaceShader;
%include "WTSurfaceShader.hpp"

%ignore WTSysInfo::WTSysInfo;
%include "WTSysInfo.hpp"

%ignore WTVector3D::WTVector3D;
%include "WTVector3D.hpp"

%ignore WTVisualizer::WTVisualizer;
%include "WTVisualizer.hpp"
