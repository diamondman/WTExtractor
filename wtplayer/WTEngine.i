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
%newobject WTObject::getOwner;
%include "WTObject.hpp"

%newobject WTContainer::getLookAt;
%newobject WTContainer::getAttached;
%ignore WTContainer::WTContainer;
%include "WTContainer.hpp"

%newobject WTGroup::getObjectByName;
%newobject WTGroup::getChildByIndex;
%ignore WTGroup::WTGroup;
%include "WTGroup.hpp"

%ignore WTActor::WTActor;
%include "WTActor.hpp"

%newobject WTAudioClip3D::getCamera;
%ignore WTAudioClip3D::WTAudioClip3D;
%include "WTAudioClip3D.hpp"

%ignore WTAudioClip::WTAudioClip;
%include "WTAudioClip.hpp"

%ignore WTBitmap::WTBitmap;
%include "WTBitmap.hpp"

%newobject WTCamera::addDrop;
%newobject WTCamera::getDrop;
%newobject WTCamera::getRenderBitmap;
%ignore WTCamera::WTCamera;
%ignore WTCamera::_render;
%include "WTCamera.hpp"

%ignore WTCollisionInfo::WTCollisionInfo;
%include "WTCollisionInfo.hpp"

%newobject WTDrop::addDrop;
%newobject WTDrop::getDrop;
%newobject WTDrop::getBitmap;
%ignore WTDrop::WTDrop;
%ignore WTDrop::_render;
%include "WTDrop.hpp"

//The WTEvent constructor is necessary, for now at least.
%newobject WTEvent::getStage;
%newobject WTEvent::getCamera;
%newobject WTEvent::getObject;
%include "WTEvent.hpp"

%ignore WTFile::WTFile;
%include "WTFile.hpp"

%ignore WTFont::WTFont;
%include "WTFont.hpp"

%newobject WT::createStage;
%newobject WT::createBox;
%newobject WT::createStage;
%newobject WT::createModel;
%newobject WT::createContainer;
%newobject WT::createLight;
%newobject WT::createGroup;
%newobject WT::createBlankBitmap;
%newobject WT::createBitmap;
%newobject WT::createAudioClip;
%newobject WT::createAudioVisualizer;
%newobject WT::createLine;
%newobject WT::createCone;
%newobject WT::createCylinder;
%newobject WT::createPlane;
%newobject WT::createPatch;
%newobject WT::createSphere;
%newobject WT::createJoystick;
%newobject WT::createGroupFromFile;
%newobject WT::createActor;
%newobject WT::createSurfaceShader;
%newobject WT::createFont;
%newobject WT::createAudioClip3D;
%newobject WT::createSpout;
%newobject WT::createPortal;
%newobject WT::createMesh;
%newobject WT::createBlankMesh;
%newobject WT::createString3D;
%newobject WT::createShadow;
%newobject WT::readFile;
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

%newobject WTPortal::getCamera;
%ignore WTPortal::WTPortal;
%include "WTPortal.hpp"

%ignore WTShadow::WTShadow;
%include "WTShadow.hpp"

%ignore WTSpout::WTSpout;
%include "WTSpout.hpp"

%newobject WTStage::getObjectByName;
%newobject WTStage::getChildByIndex;
%newobject WTStage::createCamera;
%newobject WTStage::createBitmapCamera;
%ignore WTStage::WTStage;
%ignore WTStage::_render;
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
