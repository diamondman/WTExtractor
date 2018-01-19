#include "basetypes.hpp"
#include "WTCamera.hpp"
#include "WTBitmap.hpp"
#include "WTDrop.hpp"
#include "WTVector3D.hpp"
#include "WTCollisionInfo.hpp"

void WTCamera::setZoom(int Zoom_Factor){
  APILOG;
}

void WTCamera::setViewRect(int x,
                           int y,
                           int Width,
                           int Height){
  APILOG;
}

WTDrop* WTCamera::addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                          bool Put_Drop_In_Front){
  APILOG;
  return new WTDrop();
}

void WTCamera::removeDrop(WTDrop* Drop_To_Remove){
  APILOG;
}

WTDrop* WTCamera::getDrop(int Drop_Number){
  APILOG;
  return 0;
}

int WTCamera::getDropCount(bool Count_Front_Drops){
  APILOG;
  return 0;
}

void WTCamera::setViewHWND(int hWnd){
  APILOG;
}

void WTCamera::setFieldOfView(float Field_Of_View){
  APILOG;
}

int WTCamera::suspend(bool Maintain_Image){
  APILOG;
  return 0;
}

int WTCamera::resume(){
  APILOG;
  return 0;
}

void WTCamera::setClipping(float Back_Clipping_Plane,
                           float Front_Clipping_Plane){
  APILOG;
}

WTVector3D* WTCamera::screenPointToWorldPoint(int x,
                                              int y,
                                              float Distance_From_Camera){
  APILOG;
  return new WTVector3D();
}

WTVector3D* WTCamera::worldPointToScreenPoint(float x,
                                              float y,
                                              float Z){
  APILOG;
  return new WTVector3D();
}

WTCollisionInfo* WTCamera::pick(int x,
                                int y){
  APILOG;
  return 0;
}

WTBitmap* WTCamera::getRenderBitmap(){
  APILOG;
  return 0;
}

void WTCamera::setRenderPriority(int Priority){
  APILOG;
}

int WTCamera::getRenderPriority(){
  APILOG;
  return 0;
}

void WTCamera::setBitmapClearColor(int iRed,
                                   int iGreen,
                                   int iBlue){
  APILOG;
}

void WTCamera::setUpdateFrequency(int iFrequency){
  APILOG;
}
