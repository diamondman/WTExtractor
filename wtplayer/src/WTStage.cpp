#include "basetypes.hpp"
#include "WTStage.hpp"
#include "WTCamera.hpp"
#include "WTContainer.hpp"

#include <string.h>

WTStage::WTStage(WT* wt_) :
  WTObject(wt_) {
}

WTStage::~WTStage() {
  for(auto o : this->objects)
    o->Release();

  for(auto c : this->cameras)
    c->Release();

  for(auto c : this->bitmapCameras)
    c->Release();
}

void WTStage::addObject(WTContainer* o){
  APILOG;
  o->AddRef();
  this->objects.push_back(o);
}

void WTStage::removeObject(WTContainer* o){
  APILOG;
  for(int i = 0; i < this->objects.size(); i++) {
    if(this->objects[i] == o){
      o->Release();
      this->objects.erase(this->objects.begin() + i);
      return;
    }
  }
  std::cout << "ERROR! Tried to remove an object that was not here! Prob our fault!\n";
}

WTObject* WTStage::getObjectByName(char* Name_Of_Object,
                                   int Nth){
  APILOG;
  if(Nth > 0)
    Nth--; //1 indexed, turning to 0 index. Ignoring issues of passing 0 for now. TODO?

  for(int i = 0; i < this->objects.size(); i++) {
    if(strcmp(this->objects[i]->getName(), Name_Of_Object) == 0){
      return this->objects[i];
    }
  }

  std::cout << "Error? getObjectByName returning null" << std::endl;
  return NULL;
}

int WTStage::getChildCount(){
  APILOG;
  return this->objects.size();
}

WTObject* WTStage::getChildByIndex(int Child_Number){
  APILOG;
  if(Child_Number >= this->objects.size())
    return NULL;
  return this->objects[Child_Number];
}

WTCamera* WTStage::createCamera(){
  APILOG;
  WTCamera* camera = new WTCamera(this->wt);
  camera->AddRef();
  this->cameras.push_back(camera);
  return camera;
}

WTCamera* WTStage::createBitmapCamera(int iWidth,
                                      int iHeight){
  APILOG;
  WTCamera* camera = new WTCamera(this->wt);
  camera->AddRef();
  this->bitmapCameras.push_back(camera);
  return camera;
}

bool WTStage::getFogEnabled(){
  APILOG;
  return this->fog_enabled;
}

void WTStage::setFogEnabled(bool Turn_On_Fog){
  APILOG;
  this->fog_enabled = Turn_On_Fog;
}

float WTStage::getFogStartDistance(){
  APILOG;
  return this->fog_start_distance;
}

void WTStage::setFogStartDistance(float Distance){
  APILOG;
  this->fog_start_distance = Distance;
}

float WTStage::getFogEndDistance(){
  APILOG;
  return this->fog_end_distance;
}

void WTStage::setFogEndDistance(float Distance){
  APILOG;
  this->fog_end_distance = Distance;
}

float WTStage::getFogDensity(){
  APILOG;
  return this->fog_density;
}

void WTStage::setFogDensity(float Density){
  APILOG;
  this->fog_density = Density;
}

void WTStage::setFogColor(unsigned char Red,
                 unsigned char Green,
                 unsigned char Blue){
  APILOG;
  this->fog_color = (Red << 16) | (Green << 8) | Blue;
}

void WTStage::setBGColor(unsigned char Red,
                unsigned char Green,
                unsigned char Blue){
  APILOG;
  this->bg_color = (Red << 16) | (Green << 8) | Blue;
}
