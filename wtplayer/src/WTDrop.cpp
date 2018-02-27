#include <cairo.h>

#include "basetypes.hpp"

#include "WTDrop.hpp"
#include "WTBitmap.hpp"

WTDrop::WTDrop(WT* wt_,
               WTBitmap* bitmap) :
  WTObject(wt_), bitmap(bitmap), width(bitmap->width), height(bitmap->height) {
  this->bitmap->AddRef();
}

WTDrop::~WTDrop() {
  this->detach();

  for(auto o : this->drops)
    o->Release();
}

void WTDrop::_render(cairo_t* cr, int x, int y) {
  APILOG;
  if(!this->visible) {
    std::cout << "  Not rendering: Drop not vislble." << std::endl;
    return;
  }
  if(this->bitmap) {
    cairo_identity_matrix(cr);
    cairo_translate(cr, x + this->pos_x, y + this->pos_y);
    //src_w = 100
    //dest_w = 200
    //scale = 2 = 200/100 = dest/src
    if(width != this->bitmap->width || height != this->bitmap->height){
      cairo_scale(cr,
                  static_cast<float>(width)/static_cast<float>(this->bitmap->width),
                  static_cast<float>(height)/static_cast<float>(this->bitmap->height));
      std::cout <<
        "  WTDrop Render Scale factor(W: " << static_cast<float>(width) << "/" <<
        static_cast<float>(this->bitmap->width) << "=" <<
        static_cast<float>(width)/static_cast<float>(this->bitmap->width) <<
        "; H: " << static_cast<float>(height) << "/" <<
        static_cast<float>(this->bitmap->height) << "=" <<
        static_cast<float>(height)/static_cast<float>(this->bitmap->height)<<
        std::endl;
    }

    cairo_set_source_surface(cr, this->bitmap->cairosurf, 0, 0);
    cairo_paint(cr);
    cairo_identity_matrix(cr);
  }

  cairo_new_path(cr);
  cairo_set_source_rgb(cr, 1.0, 1.0, 0);
  cairo_set_line_width(cr, 2.0);
  cairo_rectangle(cr,
                  this->pos_x, this->pos_y,
                  this->width, this->height);
  cairo_stroke(cr);

  printf("    Rendering %d drops\n", this->drops.size());
  for(WTDrop* drop : this->drops)
    drop->_render(cr, x + this->pos_x, y + this->pos_y);
}

void WTDrop::_moveDropToFront(WTDrop* drop) {
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

void WTDrop::_setParent(container_WTDrop* parent) {
  APILOG;
  if(this->parent) {
    this->parent->removeDrop(this);
  }
  this->parent = parent;
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
  drop->_setParent(this);
  return drop;
}

void WTDrop::removeDrop(WTDrop* o){
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

WTDrop* WTDrop::getDrop(int Drop_Number){
  APILOG;
  if (this->drops.size() > Drop_Number) {
    auto it = this->drops.begin();
    std::advance(it, Drop_Number);
    return (*it);
  }
  return NULL;
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
  printf("    parent: %p\n", this->parent);
  if(this->parent == NULL) return;
  this->parent->_moveDropToFront(this);
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
