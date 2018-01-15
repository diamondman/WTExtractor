#include "basetypes.hpp"
#include "WTDrop.hpp"
#include "WTBitmap.hpp"

WTDrop::WTDrop(){
}

WTDrop::WTDrop(WTBitmap* Bitmap_To_Use_As_Drop,
               int Z_Order){
}

int WTDrop::getWidth(){
  APILOG;
  return 0;
}

int WTDrop::getHeight(){
  APILOG;
  return 0;
}

int WTDrop::getX(){
  APILOG;
  return 0;
}

int WTDrop::getY(){
  APILOG;
  return 0;
}

int WTDrop::getBitmapWidth(){
  APILOG;
  return 0;
}

int WTDrop::getBitmapHeight(){
  APILOG;
  return 0;
}

WTDrop* WTDrop::addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                        int Z_Order){
  APILOG;
  return new WTDrop(Bitmap_To_Use_As_Drop,
                    Z_Order);
}

void WTDrop::removeDrop(WTDrop* Drop_To_Remove){
  APILOG;
}

int WTDrop::getDropCount(){
  APILOG;
  return 0;
}

WTDrop* WTDrop::getDrop(int Drop_Number){
  APILOG;
  return 0;
}

void WTDrop::setSize(int Width,
                     int Height){
  APILOG;
}

void WTDrop::setPosition(int x,
                         int y){
  APILOG;
}

//[id(0x00001f4d), hidden]
void WTDrop::stubFunction(int Angle){
  APILOG;
}

void WTDrop::bringToFront(){
  APILOG;
}

void WTDrop::sendToBack(){
  APILOG;
}

void WTDrop::setZOrder(int New_Z_Order){
  APILOG;
}

void WTDrop::attach(WTBitmap* Bitmap_To_Attach){
  APILOG;
}

void WTDrop::detach(){
  APILOG;
}

WTBitmap* WTDrop::getBitmap(){
  APILOG;
  return 0;
}

void WTDrop::setVisible(bool Make_It_Visible){
  APILOG;
}

void WTDrop::make3d(bool Make_It_ThreeD){
  APILOG;
}

void WTDrop::setFiltering(bool Make_It_Filter){
  APILOG;
}

void WTDrop::setTextureRect(float u0,
                            float v0,
                            float U1,
                            float V1){
  APILOG;
}

void WTDrop::setOpacity(int Opacity){
  APILOG;
}
