#include "basetypes.hpp"

#include "WTContainer.hpp"
#include "WTVector3D.hpp"
#include "WTOrientation3D.hpp"

WTContainer::WTContainer(WT* wt_) :
  WTObject(wt_) {
}

WTContainer::~WTContainer() {
  this->detach();
  this->unsetLookAt();
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

void WTContainer::setOrientationVector(float X_Forward,
                                       float Y_Forward,
                                       float Z_Forward,
                                       float X_Up,
                                       float Y_Up,
                                       float Z_Up){
  APILOG;
}

WTVector3D* WTContainer::getOrientationUp(){
  APILOG;
  return new WTVector3D();
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

void WTContainer::setLookAt(WTContainer* container,
                            int Look_Type){
  APILOG;
  this->unsetLookAt();
  this->container_lookat = container;
  this->container_lookat->AddRef();

}

void WTContainer::unsetLookAt(){
  APILOG;
  if(this->container_lookat) {
    this->container_lookat->Release();
    this->container_lookat = NULL;
  }
}

WTContainer* WTContainer::getLookAt(){
  APILOG;
  return this->container_lookat;
}

void WTContainer::attach(WTObject* Object_To_Attach){
  APILOG;
  this->detach();
  this->attached_object = Object_To_Attach;
  this->attached_object->AddRef();
}

void WTContainer::attachBitmap(WTObject* o,
                               float Scale_Width,
                               float Scale_Height,
                               int X_Center,
                               int Y_Center){
  APILOG;
  this->detach();
  this->attached_object = o;
  this->attached_object->AddRef();
}

void WTContainer::detach(){
  APILOG;
  if(this->attached_object) {
    this->attached_object->Release();
    this->attached_object = NULL;
  }
}

WTObject* WTContainer::getAttached(){
  APILOG;
  return this->attached_object;
}

void WTContainer::setBitmapSize(float Scale_Width,
                                float Scale_Height){
  APILOG;
}

void WTContainer::setBitmapOpacity(int Opacity){
  APILOG;
  this->opacity = Opacity;
}

void WTContainer::setScale(float x,
                           float y,
                           float Z){
  APILOG;
  this->scale_x = x;
  this->scale_y = y;
  this->scale_z = Z;
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
  this->pick_priority = Pick_Priority;
}

int WTContainer::getPickPriority(){
  APILOG;
  return this->pick_priority;
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
