#include "WTContainer.hpp"

void WTContainer::setPosition(float x,
                              float y,
                              float Z){}

WTVector3D* WTContainer::getPosition(){
  return 0;
}

void WTContainer::setAbsolutePosition(float x,
                                      float y,
                                      float Z){}

WTVector3D* WTContainer::getAbsolutePosition(){
  return 0;
}

void WTContainer::moveBy(float x,
                         float y,
                         float Z){}

void WTContainer::setOrientation(float x,
                                 float y,
                                 float Z,
                                 float Angle){}

WTOrientation3D* WTContainer::getOrientation(){
  return 0;
}

WTVector3D* WTContainer::getOrientationVector(){
  return 0;
}

WTVector3D* WTContainer::getOrientationUp(){
  return 0;
}

void WTContainer::setOrientationVector(float X_Forward,
                                       float Y_Forward,
                                       float Z_Forward,
                                       float X_Up,
                                       float Y_Up,
                                       float Z_Up){}

void WTContainer::setConstantRotation(float x,
                                      float y,
                                      float Z,
                                      float Angle){}

WTOrientation3D* WTContainer::getConstantRotation(){
  return 0;
}

void WTContainer::setRotation(float x,
                              float y,
                              float Z,
                              float Angle,
                              int Relative_To_World){}

void WTContainer::setLookAt(WTContainer* Container_To_Look_At,
                            int Look_Type){}

void WTContainer::unsetLookAt(){}

WTContainer* WTContainer::getLookAt(){
  return 0;
}

void WTContainer::attach(WTObject* Object_To_Attach){}

void WTContainer::attachBitmap(WTObject* Bitmap_To_Add,
                               float Scale_Width,
                               float Scale_Height,
                               int X_Center,
                               int Y_Center){}

void WTContainer::detach(){}

WTObject* WTContainer::getAttached(){
  return 0;
}

void WTContainer::setBitmapSize(float Scale_Width,
                                float Scale_Height){}

void WTContainer::setBitmapOpacity(int Opacity){}

void WTContainer::setScale(float x,
                           float y,
                           float Z){}

void WTContainer::setAbsoluteScale(float x,
                                   float y,
                                   float Z){}

void WTContainer::setScaleTare(){}

void WTContainer::setPickPriority(int Pick_Priority){}

int WTContainer::getPickPriority(){
  return 0;
}

void WTContainer::highlight(bool Turn_On_Highlight){}

bool WTContainer::isHighlighted(){
  return false;
}

void WTContainer::setVisible(bool Turn_On_Visibility){}

bool WTContainer::getVisible(){
  return true;
}

char* WTContainer::getPositionAsString(){
  return (char*)"";
}

char* WTContainer::getAbsolutePositionAsString(){
  return (char*)"";
}

char* WTContainer::getOrientationVectorAsString(){
  return (char*)"";
}

char* WTContainer::getOrientationUpAsString(){
  return (char*)"";
}

void WTContainer::setAbsoluteOrientation(float x,
                                         float y,
                                         float Z,
                                         float Angle){}

WTCollisionInfo* WTContainer::checkCollision(float x,
                                             float y,
                                             float Z,
                                             bool Position_Is_Relative_To_Object,
                                             int Collision_Mask,
                                             int Collision_Detail,
                                             int Collision_Flags,
                                             int Reserved){
  return 0;
}

WTVector3D* WTContainer::getAbsoluteOrientationVector(){
  return 0;
}

WTVector3D* WTContainer::getAbsoluteOrientationUp(){
  return 0;
}

void WTContainer::setAbsoluteOrientationVector(float X_Forward,
                                               float Y_Forward,
                                               float Z_Forward,
                                               float X_Up,
                                               float Y_Up,
                                               float Z_Up){}

void WTContainer::setCollisionBox(float X1,
                                  float X2,
                                  float Y1,
                                  float Y2,
                                  float Z1,
                                  float Z2,
                                  int Reserved){}

void WTContainer::setCollisionMask(int Mask,
                                   int Reserved){}

int WTContainer::getCollisionMask(){
  return 0;
}

void WTContainer::makeCollisionBox(int Box_Type,
                                   int Box_Flags,
                                   int Reserved){}

void WTContainer::attachSurfaceShader(WTSurfaceShader* Shader_To_Add,
                                      float Scale_Width,
                                      float Scale_Height,
                                      int X_Center,
                                      int Y_Center){}

void WTContainer::setBitmapOrientation(float Amount){}

void WTContainer::setBitmapTextureRect(float u0,
                                       float v0,
                                       float U1,
                                       float V1){}

WTVector3D* WTContainer::getGeometryExtents(bool Max_Extents,
                                            bool With_Children){
  return 0;
}
