#include "basetypes.hpp"
#include "WTContainer.hpp"
#include "WTVector3D.hpp"
#include "WTOrientation3D.hpp"

WTContainer::WTContainer() :
  WTObject() {
}

void WTContainer::setPosition(float x,
                              float y,
                              float Z){
  APILOG;
  this->pos_x = x;
  this->pos_y = y;
  this->pos_z = Z;
}

WTVector3D* WTContainer::getPosition(){
  APILOG;
  return new WTVector3D(this->pos_x, this->pos_y, this->pos_z);
}

void WTContainer::setAbsolutePosition(float x,
                                      float y,
                                      float Z){
  APILOG;
}

WTVector3D* WTContainer::getAbsolutePosition(){
  APILOG;
  return new WTVector3D();
}

void WTContainer::moveBy(float x,
                         float y,
                         float Z){
  APILOG;
  this->pos_x += x;
  this->pos_y += y;
  this->pos_z += Z;
}

void WTContainer::setOrientation(float x,
                                 float y,
                                 float Z,
                                 float Angle){
  APILOG;
}

WTOrientation3D* WTContainer::getOrientation(){
  APILOG;
  return 0;
}

WTVector3D* WTContainer::getOrientationVector(){
  APILOG;
  return new WTVector3D();
}

WTVector3D* WTContainer::getOrientationUp(){
  APILOG;
  return new WTVector3D();
}

void WTContainer::setOrientationVector(float X_Forward,
                                       float Y_Forward,
                                       float Z_Forward,
                                       float X_Up,
                                       float Y_Up,
                                       float Z_Up){
  APILOG;
}

void WTContainer::setConstantRotation(float x,
                                      float y,
                                      float Z,
                                      float Angle){
  APILOG;
}

WTOrientation3D* WTContainer::getConstantRotation(){
  APILOG;
  return new WTOrientation3D();
}

void WTContainer::setRotation(float x,
                              float y,
                              float Z,
                              float Angle,
                              int Relative_To_World){
  APILOG;
}

void WTContainer::setLookAt(WTContainer* Container_To_Look_At,
                            int Look_Type){
  APILOG;
}

void WTContainer::unsetLookAt(){
  APILOG;
}

WTContainer* WTContainer::getLookAt(){
  APILOG;
  return 0;
}

void WTContainer::attach(WTObject* Object_To_Attach){
  APILOG;
}

void WTContainer::attachBitmap(WTObject* Bitmap_To_Add,
                               float Scale_Width,
                               float Scale_Height,
                               int X_Center,
                               int Y_Center){
  APILOG;
}

void WTContainer::detach(){
  APILOG;
}

WTObject* WTContainer::getAttached(){
  APILOG;
  return 0;
}

void WTContainer::setBitmapSize(float Scale_Width,
                                float Scale_Height){
  APILOG;
}

void WTContainer::setBitmapOpacity(int Opacity){
  APILOG;
}

void WTContainer::setScale(float x,
                           float y,
                           float Z){
  APILOG;
}

void WTContainer::setAbsoluteScale(float x,
                                   float y,
                                   float Z){
  APILOG;
}

void WTContainer::setScaleTare(){
  APILOG;
}

void WTContainer::setPickPriority(int Pick_Priority){
  APILOG;
}

int WTContainer::getPickPriority(){
  APILOG;
  return 0;
}

void WTContainer::highlight(bool Turn_On_Highlight){
  APILOG;
  this->is_highlighted = Turn_On_Highlight;
}

bool WTContainer::isHighlighted(){
  APILOG;
  return this->is_highlighted;
}

void WTContainer::setVisible(bool Turn_On_Visibility){
  APILOG;
  this->is_visible = Turn_On_Visibility;
}

bool WTContainer::getVisible(){
  APILOG;
  return this->is_visible;
}

char* WTContainer::getPositionAsString(){
  APILOG;
  return (char*)"";
}

char* WTContainer::getAbsolutePositionAsString(){
  APILOG;
  return (char*)"";
}

char* WTContainer::getOrientationVectorAsString(){
  APILOG;
  return (char*)"";
}

char* WTContainer::getOrientationUpAsString(){
  APILOG;
  return (char*)"";
}

void WTContainer::setAbsoluteOrientation(float x,
                                         float y,
                                         float Z,
                                         float Angle){
  APILOG;
}

WTCollisionInfo* WTContainer::checkCollision(float x,
                                             float y,
                                             float Z,
                                             bool Position_Is_Relative_To_Object,
                                             int Collision_Mask,
                                             int Collision_Detail,
                                             int Collision_Flags,
                                             int Reserved){
  APILOG;
  return 0;
}

WTVector3D* WTContainer::getAbsoluteOrientationVector(){
  APILOG;
  return new WTVector3D();
}

WTVector3D* WTContainer::getAbsoluteOrientationUp(){
  APILOG;
  return new WTVector3D();
}

void WTContainer::setAbsoluteOrientationVector(float X_Forward,
                                               float Y_Forward,
                                               float Z_Forward,
                                               float X_Up,
                                               float Y_Up,
                                               float Z_Up){
  APILOG;
}

void WTContainer::setCollisionBox(float X1,
                                  float X2,
                                  float Y1,
                                  float Y2,
                                  float Z1,
                                  float Z2,
                                  int Reserved){
  APILOG;
}

void WTContainer::setCollisionMask(int Mask,
                                   int Reserved){
  APILOG;
}

int WTContainer::getCollisionMask(){
  APILOG;
  return 0;
}

void WTContainer::makeCollisionBox(int Box_Type,
                                   int Box_Flags,
                                   int Reserved){
  APILOG;
}

void WTContainer::attachSurfaceShader(WTSurfaceShader* Shader_To_Add,
                                      float Scale_Width,
                                      float Scale_Height,
                                      int X_Center,
                                      int Y_Center){
  APILOG;
}

void WTContainer::setBitmapOrientation(float Amount){
  APILOG;
}

void WTContainer::setBitmapTextureRect(float u0,
                                       float v0,
                                       float U1,
                                       float V1){
  APILOG;
}

WTVector3D* WTContainer::getGeometryExtents(bool Max_Extents,
                                            bool With_Children){
  APILOG;
  return new WTVector3D();
}
