#include "basetypes.hpp"
#include "WTPortal.hpp"
#include "WTBitmap.hpp"
#include "WTCamera.hpp"
#include "WTSurfaceShader.hpp"

WTPortal::WTPortal(WT* wt_,
                   float Width,
                   float Height,
                   WTCamera* pCam,
                   int mappingOption,
                   bool doubleSided,
                   bool renderOnlyChildren) :
  WTGroup(wt_), camera(pCam) {
  this->camera->AddRef();
}

WTPortal::~WTPortal() {
  if(this->camera)
    this->camera->Release();
  this->camera = NULL;

  if(this->texture)
    this->texture->Release();
  this->texture = NULL;

  if(this->shader)
    this->shader->Release();
  this->shader = NULL;
}

void WTPortal::setMappingOption(int mappingOption,
                                float zScale){
  APILOG;
}

void WTPortal::setCamera(WTCamera* newPCam){
  APILOG;
  if(this->camera)
    this->camera->Release();
  this->camera = newPCam;
  this->camera->AddRef();
}

void WTPortal::setDoubleSided(bool doubleSided){
  APILOG;
}

void WTPortal::setCustomTransform(int transformOption,
                                  float xAxis,
                                  float yAxis,
                                  float zAxis) {
  APILOG;
}

void WTPortal::setTexture(WTBitmap* pBitmap,
                          int newAlpha){
  APILOG;
  if(this->texture)
    this->texture->Release();
  this->texture = pBitmap;
  this->texture->AddRef();
}

void WTPortal::setRenderOnlyChildren(bool renderOnlyChildren){
  APILOG;
}

void WTPortal::setSurfaceShader(WTSurfaceShader* pShader,
                                int newAlpha){
  APILOG;
  if(this->shader)
    this->shader->Release();
  this->shader = pShader;
  this->shader->AddRef();
}
