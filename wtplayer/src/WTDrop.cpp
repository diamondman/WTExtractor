#include "WTDrop.hpp"
#include "WTBitmap.hpp"

int WTDrop::getWidth(){
  return 0;
}

int WTDrop::getHeight(){
  return 0;
}

int WTDrop::getX(){
  return 0;
}

int WTDrop::getY(){
  return 0;
}

int WTDrop::getBitmapWidth(){
  return 0;
}

int WTDrop::getBitmapHeight(){
  return 0;
}

WTDrop* WTDrop::addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                        int Z_Order){
  return 0;
}

void WTDrop::removeDrop(WTDrop* Drop_To_Remove){}

int WTDrop::getDropCount(){
  return 0;
}

WTDrop* WTDrop::getDrop(int Drop_Number){
  return 0;
}

void WTDrop::setSize(int Width,
                     int Height){}

void WTDrop::setPosition(int x,
                         int y){}

//[id(0x00001f4d), hidden]
void WTDrop::stubFunction(int Angle){}

void WTDrop::bringToFront(){}

void WTDrop::sendToBack(){}

void WTDrop::setZOrder(int New_Z_Order){}

void WTDrop::attach(WTBitmap* Bitmap_To_Attach){}

void WTDrop::detach(){}

WTBitmap* WTDrop::getBitmap(){
  return 0;
}

void WTDrop::setVisible(bool Make_It_Visible){}

void WTDrop::make3d(bool Make_It_ThreeD){}

void WTDrop::setFiltering(bool Make_It_Filter){}

void WTDrop::setTextureRect(float u0,
                            float v0,
                            float U1,
                            float V1){}

void WTDrop::setOpacity(int Opacity){}
