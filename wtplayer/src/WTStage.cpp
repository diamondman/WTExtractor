#include "basetypes.hpp"
#include "WTStage.hpp"
#include "WTCamera.hpp"
#include "WTContainer.hpp"

WTStage::WTStage() :
  WTObject() {
}

void WTStage::addObject(WTContainer* Object_To_Add){
  APILOG;
}

void WTStage::removeObject(WTContainer* Object_To_Remove){
  APILOG;
}

WTCamera* WTStage::createCamera(){
  APILOG;
  return new WTCamera();
}

bool WTStage::getFogEnabled(){
  APILOG;
  return false;
}

void WTStage::setFogEnabled(bool Turn_On_Fog){
  APILOG;
}

float WTStage::getFogStartDistance(){
  APILOG;
  return 0;
}

void WTStage::setFogStartDistance(float Distance){
  APILOG;
}

float WTStage::getFogEndDistance(){
  APILOG;
  return 0;
}

void WTStage::setFogEndDistance(float Distance){
  APILOG;
}

float WTStage::getFogDensity(){
  APILOG;
  return 0;
}

void WTStage::setFogDensity(float Density){
  APILOG;
}

void WTStage::setFogColor(unsigned char Red,
                 unsigned char Green,
                 unsigned char Blue){
  APILOG;
}

void WTStage::setBGColor(unsigned char Red,
                unsigned char Green,
                unsigned char Blue){
  APILOG;
}

WTObject* WTStage::getObjectByName(char* Name_Of_Object,
                                     int Nth){
  APILOG;
  return 0;
}

int WTStage::getChildCount(){
  APILOG;
  return 0;
}

WTObject* WTStage::getChildByIndex(int Child_Number){
  APILOG;
  return 0;
}

WTCamera* WTStage::createBitmapCamera(int iWidth,
                                      int iHeight){
  APILOG;
  return new WTCamera();
}
