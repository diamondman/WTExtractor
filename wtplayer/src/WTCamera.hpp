#pragma once

#include <vector>

#include "WTContainer.hpp"

class WTBitmap;
class WTDrop;
class WTVector3D;
class WTCollisionInfo;

class WTCamera : public WTContainer {

public:
  friend class WTDrop;

  WTCamera(WT* wt_);

  WTCamera(WT* wt_,
           WTBitmap* bitmap);

  virtual ~WTCamera();

  typedef struct _cairo cairo_t;
  void _render(cairo_t* cr);

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

  int getDropCount(bool Count_Front_Drops = false){
    APILOG;
    return this->drops.size();
  }

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

  void setRenderPriority(int Priority) {
    APILOG;
    this->render_priority = Priority;
  }

  int getRenderPriority() {
    APILOG;
    return render_priority;
  }

  void setBitmapClearColor(int Red,
                           int Green,
                           int Blue) {
    APILOG;
    this->bitmap_clear_color =
      (((uint8_t)Red)   << 16) |
      (((uint8_t)Green) << 8 ) |
      ((uint8_t)Blue);
  }

  void setUpdateFrequency(int Frequency) {
    APILOG;
    this->update_frequency = Frequency;
  }

private:
  std::vector<WTDrop*> drops;
  WTBitmap* render_bitmap = NULL;

  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;

  int render_priority = 0;
  uint32_t bitmap_clear_color = 0;
  int update_frequency = 0;
};
