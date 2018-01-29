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
  WTGroup(wt_) {
}

void WTPortal::setMappingOption(int mappingOption,
                      float zScale){
  APILOG;
}

void WTPortal::setCamera(WTCamera* newPCam){
  APILOG;
}

void WTPortal::setDoubleSided(bool doubleSided){
  APILOG;
}

void WTPortal::setCustomTransform(int transformOption,
                        float xAxis,
                        float yAxis,
                        float zAxis){
  APILOG;
}

void WTPortal::setTexture(WTBitmap* pBitmap,
                int newAlpha){
  APILOG;
}

void WTPortal::setRenderOnlyChildren(bool renderOnlyChildren){
  APILOG;
}

WTCamera* WTPortal::getCamera(){
  APILOG;
  return 0;
}

void WTPortal::setSurfaceShader(WTSurfaceShader* pShader,
                      int newAlpha){
  APILOG;
}
