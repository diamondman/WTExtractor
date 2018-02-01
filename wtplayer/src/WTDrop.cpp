#include "basetypes.hpp"
#include "WTDrop.hpp"
#include "WTBitmap.hpp"

#include <cairo.h>

WTDrop::WTDrop(WT* wt_,
               WTBitmap* bitmap) :
  WTObject(wt_), bitmap(bitmap) {
  this->bitmap->AddRef();
}

WTDrop::~WTDrop() {
  this->detach();

  for(auto o : this->drops)
    o->Release();
}

void WTDrop::_render(cairo_t* cr, int x, int y) {
  if(this->bitmap) {
    cairo_set_source_surface(cr, this->bitmap->cairosurf,
                             x + this->pos_x, y + this->pos_y);
    cairo_paint(cr);
  }

  cairo_set_source_rgb(cr, 1.0, 0, 0);
  cairo_set_line_width(cr, 1.0);
  cairo_rectangle(cr,
                  this->pos_x, this->pos_y,
                  this->width, this->height);
  cairo_stroke(cr);

  for(WTDrop* drop : this->drops)
    drop->_render(cr, x + this->pos_x, y + this->pos_y);
}

int WTDrop::getBitmapWidth(){
  APILOG;
  if(this->bitmap)
    return this->bitmap->getWidth();
  return 0;
}

int WTDrop::getBitmapHeight(){
  APILOG;
  if(this->bitmap)
    return this->bitmap->getHeight();
  return 0;
}

WTDrop* WTDrop::addDrop(WTBitmap* Bitmap_To_Use_As_Drop,
                        int Z_Order){
  APILOG;
  WTDrop* drop = new WTDrop(this->wt,
                            Bitmap_To_Use_As_Drop);
  drop->AddRef();
  this->drops.push_back(drop);
  return drop;
}

void WTDrop::removeDrop(WTDrop* o){
  APILOG;
  for(int i = 0; i < this->drops.size(); i++) {
    if(this->drops[i] == o){
      o->Release();
      this->drops.erase(this->drops.begin() + i);
      return;
    }
  }
  std::cout << "ERROR! Tried to remove an drop that was not here! Prob our fault!\n";
}

WTDrop* WTDrop::getDrop(int Drop_Number){
  APILOG;
  if(Drop_Number >= this->drops.size())
    return NULL;
  return this->drops[Drop_Number];
}

void WTDrop::setSize(int Width,
                     int Height){
  APILOG;
  std::cout << "  (" << Width << ", " << Height << ")" << std::endl;
  this->width = Width;
  this->height = Height;
}

void WTDrop::setPosition(int x,
                         int y){
  APILOG;
  std::cout << "  (" << x << ", " << y << ")" << std::endl;
  this->pos_x = x;
  this->pos_y = y;
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

void WTDrop::attach(WTBitmap* bitmap){
  APILOG;
  this->detach();
  this->bitmap = bitmap;
  this->bitmap->AddRef();
}

void WTDrop::detach(){
  APILOG;
  if(this->bitmap) {
    this->bitmap->Release();
    this->bitmap = NULL;
  }
}

void WTDrop::make3d(bool b){
  APILOG;
}

void WTDrop::setTextureRect(float u0,
                            float v0,
                            float U1,
                            float V1){
  APILOG;
}
