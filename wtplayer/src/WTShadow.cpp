#include "basetypes.hpp"
#include "WTShadow.hpp"

int WTShadow::getType(){
  APILOG;
  return 0;
}

void WTShadow::setEnable(bool enabled){
  APILOG;
}

bool WTShadow::getEnable(){
  APILOG;
  return false;
}

void WTShadow::setFieldOfView(float Fov){
  APILOG;
}

float WTShadow::getFieldOfView(){
  APILOG;
  return 0;
}

void WTShadow::setResolution(int Width,
                   int Height){
  APILOG;
}

int WTShadow::getWidth(){
  APILOG;
  return 0;
}

int WTShadow::getHeight(){
  APILOG;
  return 0;
}

void WTShadow::addCaster(WTGroup* Group_To_Add,
               int Red,
               int Green,
               int Blue){
  APILOG;
}

void WTShadow::removeCaster(WTGroup* Group_To_Remove){
  APILOG;
}

void WTShadow::addReceiver(WTGroup* Group_To_Add){
  APILOG;
}

void WTShadow::removeReceiver(WTGroup* Group_To_Remove){
  APILOG;
}

void WTShadow::setCasterColor(WTGroup* Group,
                    int Red,
                    int Green,
                    int Blue){
  APILOG;
}

int WTShadow::getCasterColorRed(WTGroup* Group){
  APILOG;
  return 0;
}

int WTShadow::getCasterColorGreen(WTGroup* Group){
  APILOG;
  return 0;
}

int WTShadow::getCasterColorBlue(WTGroup* Group){
  APILOG;
  return 0;
}

void WTShadow::setFiltering(int FilteringMethod){
  APILOG;
}

int WTShadow::getFiltering(){
  APILOG;
  return 0;
}

void WTShadow::setRange(bool RelativeToCaster,
              float Near,
              float Far){
  APILOG;
}

void WTShadow::enableCulling(bool Enable,
                   bool EnableExtraCullPlanes){
  APILOG;
}
