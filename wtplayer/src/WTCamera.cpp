#include <cairo.h>

#include "basetypes.hpp"

#include "WTCamera.hpp"
#include "WTBitmap.hpp"
#include "WTDrop.hpp"
#include "WTVector3D.hpp"
#include "WTCollisionInfo.hpp"

WTCamera::WTCamera(WT* wt_) :
  WTContainer(wt_) {
}

WTCamera::WTCamera(WT* wt_,
                   WTBitmap* bitmap) :
  WTContainer(wt_), render_bitmap(bitmap) {
  this->render_bitmap->AddRef();
}

WTCamera::~WTCamera() {
  if(this->render_bitmap) {
    this->render_bitmap->Release();
    this->render_bitmap = NULL;
  }

  for(auto o : this->drops)
    o->Release();
}

void WTCamera::_render(cairo_t* cr) {
  APILOG;
  cairo_new_path(cr);
  cairo_set_source_rgb(cr, 1.0, 0, 0);
  cairo_set_line_width(cr, 4.0);
  cairo_rectangle(cr, this->x, this->y, this->width, this->height);
  cairo_stroke(cr);

  printf("  Rendering %d drops\n", this->drops.size());
  for(WTDrop* drop : this->drops)
    drop->_render(cr, 0, 0);
}

void WTCamera::_moveDropToFront(WTDrop* drop) {
  APILOG;
  //printf("Prev Drop Order: ");
  //for(WTDrop* d : this->drops)
  //  printf("%p ", d);
  //printf("\n    Moving drop to front %p\n", drop);

  for(auto it = this->drops.begin(); it != this->drops.end(); ++it) {
    if(*it == drop){
      this->drops.splice(this->drops.end(), this->drops, it);

      //printf("Post Drop Order: ");
      //for(WTDrop* d : this->drops)
      //  printf("%p ", d);
      //printf("\n");

      return;
    }
  }
  std::cout << "ERROR! Tried to move a drop to the front that was not here! Prob our fault!\n";

}

void WTCamera::setZoom(int Zoom_Factor){
  APILOG;
}

void WTCamera::setViewRect(int x,
                           int y,
                           int Width,
                           int Height){
  APILOG;
  this->x = x;
  this->y = y;
  this->width = Width;
  this->height = Height;
}

WTDrop* WTCamera::addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                          bool Put_Drop_In_Front){
  APILOG;
  WTDrop* drop = new WTDrop(this->wt,
                            Bitmap_To_Use_As_Drop);
  drop->AddRef();
  this->drops.push_back(drop);
  drop->_setParent(this);
  return drop;
}

void WTCamera::removeDrop(WTDrop* o){
  APILOG;
    for(auto it = this->drops.begin(); it != this->drops.end(); ++it) {
    if(*it == o){
      (*it)->Release();
      this->drops.erase(it);
      return;
    }
  }
  std::cout << "ERROR! Tried to remove an drop that was not here! Prob our fault!\n";
}

WTDrop* WTCamera::getDrop(int Drop_Number){
  APILOG;
  if (this->drops.size() > Drop_Number) {
    auto it = this->drops.begin();
    std::advance(it, Drop_Number);
    return (*it);
  }
  return NULL;
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
  return this->render_bitmap;
}
