#pragma once

#include "WTObject.hpp"

class WTBitmap;

class WTDrop : public WTObject {

public:
  WTDrop();

  WTDrop(WTBitmap* Bitmap_To_Use_As_Drop,
         int Z_Order);

  int getWidth();

  int getHeight();

  int getX();

  int getY();

  int getBitmapWidth();

  int getBitmapHeight();

  WTDrop* addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                  int Z_Order = -1);

  void removeDrop(WTDrop* Drop_To_Remove);

  int getDropCount();

  WTDrop* getDrop(int Drop_Number);

  void setSize(int Width,
               int Height);

  void setPosition(int x,
                   int y);

  //[id(0x00001f4d), hidden]
  void stubFunction(int Angle);

  void bringToFront();

  void sendToBack();

  void setZOrder(int New_Z_Order);

  void attach(WTBitmap* Bitmap_To_Attach);

  void detach();

  WTBitmap* getBitmap();

  void setVisible(bool Make_It_Visible);

  void make3d(bool Make_It_ThreeD = true);

  void setFiltering(bool Make_It_Filter = true);

  void setTextureRect(float u0,
                      float v0,
                      float U1,
                      float V1);

  void setOpacity(int Opacity);
};
