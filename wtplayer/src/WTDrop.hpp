#pragma once

#include <list>

#include "container_WTDrop.hpp"

#include "WTObject.hpp"

class WTBitmap;

class WTDrop : public WTObject, public container_WTDrop {

public:
  WTDrop(WT* wt_,
         WTBitmap* Bitmap_To_Use_As_Drop);

  virtual ~WTDrop();

  typedef struct _cairo cairo_t;
  virtual void _render(cairo_t* cr, int x, int y);
  virtual void _moveDropToFront(WTDrop* drop);
  void _setParent(container_WTDrop* parent);

  int getObjectType(){
    APILOG;
    return this->WTObject::getObjectType() |
      WT_2D |
      WTDROP;
  }

  int getWidth(){
    APILOG;
    return this->width;
  }

  int getHeight(){
    APILOG;
    return this->height;
  }

  int getX(){
    APILOG;
    return this->pos_x;
  }

  int getY(){
    APILOG;
    return this->pos_y;
  }

  int getBitmapWidth();

  int getBitmapHeight();

  WTDrop* addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                  int Z_Order = -1);

  void removeDrop(WTDrop* Drop_To_Remove);

  int getDropCount(){
    APILOG;
    return this->drops.size();
  }

  WTDrop* getDrop(int Drop_Number);

  void setSize(int Width,
               int Height);

  void setPosition(int x,
                   int y);

  void bringToFront();

  void sendToBack();

  void setZOrder(int New_Z_Order);

  void attach(WTBitmap* Bitmap_To_Attach);

  void detach();

  WTBitmap* getBitmap(){
    APILOG;
    return this->bitmap;
  }

  void setVisible(bool b){
    APILOG;
    this->visible = b;
  }

  void make3d(bool Make_It_ThreeD = true);

  void setFiltering(bool b = true){
    APILOG;
    this->filter = b;
  }

  void setTextureRect(float u0,
                      float v0,
                      float U1,
                      float V1);

  void setOpacity(int Opacity){
    APILOG;
    this->opacity = Opacity;
  }

private:
  WTBitmap* bitmap = NULL;
  std::list<WTDrop*> drops;
  container_WTDrop* parent = NULL;

  unsigned int pos_x = 0;
  unsigned int pos_y = 0;

  unsigned int width = 0;
  unsigned int height = 0;

  uint8_t opacity = 0xFF;

  bool visible = true;
  bool filter = false;
};
