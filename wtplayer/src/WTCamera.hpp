#pragma once

#include "WTContainer.hpp"

class WTBitmap;
class WTDrop;
class WTVector3D;
class WTCollisionInfo;

class WTCamera : public WTContainer {

public:
  WTCamera();

  int getObjectType(){
    APILOG;
    return WTContainer::getObjectType() |
      WT_3D |
      WTCAMERA;
  }

  //[id(0x00001771), hidden]
  void setZoom(int Zoom_Factor);

  void setViewRect(int x,
                   int y,
                   int Width,
                   int Height);

  WTDrop* addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                  bool Put_Drop_In_Front = false);

  void removeDrop(WTDrop* Drop_To_Remove);

  WTDrop* getDrop(int Drop_Number);

  int getDropCount(bool Count_Front_Drops = false);

  void setViewHWND(int hWnd);

  void setFieldOfView(float Field_Of_View);

  int suspend(bool Maintain_Image = true);

  int resume();

  void setClipping(float Back_Clipping_Plane,
                   float Front_Clipping_Plane = 1);

  WTVector3D* screenPointToWorldPoint(int x,
                                      int y,
                                      float Distance_From_Camera);

  WTVector3D* worldPointToScreenPoint(float x,
                                      float y,
                                      float Z);

  WTCollisionInfo* pick(int x,
                        int y);

  WTBitmap* getRenderBitmap();

  void setRenderPriority(int Priority);

  int getRenderPriority();

  void setBitmapClearColor(int iRed,
                           int iGreen,
                           int iBlue);

  void setUpdateFrequency(int iFrequency);
};
