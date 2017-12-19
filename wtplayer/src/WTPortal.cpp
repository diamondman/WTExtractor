#include "WTPortal.hpp"
#include "WTBitmap.hpp"
#include "WTCamera.hpp"
#include "WTSurfaceShader.hpp"

void WTPortal::setMappingOption(int mappingOption,
                      float zScale){}

void WTPortal::setCamera(WTCamera* newPCam){}

void WTPortal::setDoubleSided(bool doubleSided){}

void WTPortal::setCustomTransform(int transformOption,
                        float xAxis,
                        float yAxis,
                        float zAxis){}

void WTPortal::setTexture(WTBitmap* pBitmap,
                int newAlpha){}

void WTPortal::setRenderOnlyChildren(bool renderOnlyChildren){}

WTCamera* WTPortal::getCamera(){
  return 0;
}

void WTPortal::setSurfaceShader(WTSurfaceShader* pShader,
                      int newAlpha){}
