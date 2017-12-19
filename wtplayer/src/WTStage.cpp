#include "WTStage.hpp"
#include "WTCamera.hpp"
#include "WTContainer.hpp"

void WTStage::addObject(WTContainer* Object_To_Add){}

void WTStage::removeObject(WTContainer* Object_To_Remove){}

WTCamera* WTStage::createCamera(){
  return 0;
}

bool WTStage::getFogEnabled(){
  return false;
}

void WTStage::setFogEnabled(bool Turn_On_Fog){}

float WTStage::getFogStartDistance(){
  return 0;
}

void WTStage::setFogStartDistance(float Distance){}

float WTStage::getFogEndDistance(){
  return 0;
}

void WTStage::setFogEndDistance(float Distance){}

float WTStage::getFogDensity(){
  return 0;
}

void WTStage::setFogDensity(float Density){}

void WTStage::setFogColor(unsigned char Red,
                 unsigned char Green,
                 unsigned char Blue){}

void WTStage::setBGColor(unsigned char Red,
                unsigned char Green,
                unsigned char Blue){}

WTObject* WTStage::getObjectByName(char* Name_Of_Object,
                                     int Nth){
  return 0;
}

int WTStage::getChildCount(){
  return 0;
}

WTObject* WTStage::getChildByIndex(int Child_Number){
  return 0;
}

WTCamera* WTStage::createBitmapCamera(int iWidth,
                                      int iHeight){
  return 0;
}
