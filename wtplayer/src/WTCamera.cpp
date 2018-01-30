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
  WTDrop* drop = new WTDrop(this->wt,
                            Bitmap_To_Use_As_Drop);
  drop->AddRef();
  this->drops.push_back(drop);
  return drop;
}

void WTCamera::removeDrop(WTDrop* o){
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

WTDrop* WTCamera::getDrop(int Drop_Number){
  APILOG;
  if(Drop_Number >= this->drops.size())
    return NULL;
  return this->drops[Drop_Number];
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
