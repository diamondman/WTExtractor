#include "WTShadow.hpp"

int WTShadow::getType(){
  return 0;
}

void WTShadow::setEnable(bool enabled){}

bool WTShadow::getEnable(){
  return false;
}

void WTShadow::setFieldOfView(float Fov){}

float WTShadow::getFieldOfView(){
  return 0;
}

void WTShadow::setResolution(int Width,
                   int Height){}

int WTShadow::getWidth(){
  return 0;
}

int WTShadow::getHeight(){
  return 0;
}

void WTShadow::addCaster(WTGroup* Group_To_Add,
               int Red,
               int Green,
               int Blue){}

void WTShadow::removeCaster(WTGroup* Group_To_Remove){}

void WTShadow::addReceiver(WTGroup* Group_To_Add){}

void WTShadow::removeReceiver(WTGroup* Group_To_Remove){}

void WTShadow::setCasterColor(WTGroup* Group,
                    int Red,
                    int Green,
                    int Blue){}

int WTShadow::getCasterColorRed(WTGroup* Group){
  return 0;
}

int WTShadow::getCasterColorGreen(WTGroup* Group){
  return 0;
}

int WTShadow::getCasterColorBlue(WTGroup* Group){
  return 0;
}

void WTShadow::setFiltering(int FilteringMethod){}

int WTShadow::getFiltering(){
  return 0;
}

void WTShadow::setRange(bool RelativeToCaster,
              float Near,
              float Far){}

void WTShadow::enableCulling(bool Enable,
                   bool EnableExtraCullPlanes){}
