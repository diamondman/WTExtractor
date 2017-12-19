#include "WTCamera.hpp"

class WTBitmap;
class WTDrop;
class WTVector3D;
class WTCollisionInfo;

void WTCamera::setZoom(int Zoom_Factor){}

void WTCamera::setViewRect(int x,
                           int y,
                           int Width,
                           int Height){}

WTDrop* WTCamera::addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                          bool Put_Drop_In_Front){
  return 0;
}

void WTCamera::removeDrop(WTDrop* Drop_To_Remove){}

WTDrop* WTCamera::getDrop(int Drop_Number){
  return 0;
}

int WTCamera::getDropCount(bool Count_Front_Drops){
  return 0;
}

void WTCamera::setViewHWND(int hWnd){}

void WTCamera::setFieldOfView(float Field_Of_View){}

int WTCamera::suspend(bool Maintain_Image){
  return 0;
}

int WTCamera::resume(){
  return 0;
}

void WTCamera::setClipping(float Back_Clipping_Plane,
                           float Front_Clipping_Plane){}

WTVector3D* WTCamera::screenPointToWorldPoint(int x,
                                              int y,
                                              float Distance_From_Camera){
  return 0;
}

WTVector3D* WTCamera::worldPointToScreenPoint(float x,
                                              float y,
                                              float Z){
  return 0;
}

WTCollisionInfo* WTCamera::pick(int x,
                                int y){
  return 0;
}

WTBitmap* WTCamera::getRenderBitmap(){
  return 0;
}

void WTCamera::setRenderPriority(int Priority){}

int WTCamera::getRenderPriority(){
  return 0;
}

void WTCamera::setBitmapClearColor(int iRed,
                                   int iGreen,
                                   int iBlue){}

void WTCamera::setUpdateFrequency(int iFrequency){}
