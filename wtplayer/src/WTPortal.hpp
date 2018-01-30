#pragma once

#include "WTGroup.hpp"

class WTBitmap;
class WTCamera;
class WTSurfaceShader;

class WTPortal : public WTGroup {

public:
  WTPortal(WT* wt_,
           float Width,
           float Height,
           WTCamera* pCam,
           int mappingOption,
           bool doubleSided,
           bool renderOnlyChildren);

  virtual ~WTPortal();

  int getObjectType(){
    APILOG;
    return this->WTGroup::getObjectType() |
      WTPORTAL;
  }

  void setMappingOption(int mappingOption,
                        float zScale = 100);

  void setCamera(WTCamera* newPCam);

  void setDoubleSided(bool doubleSided);

  void setCustomTransform(int transformOption,
                          float xAxis,
                          float yAxis,
                          float zAxis);

  void setTexture(WTBitmap* pBitmap,
                  int newAlpha = 255);

  void setRenderOnlyChildren(bool renderOnlyChildren);

  WTCamera* getCamera() {
    return this->camera;
  }

  void setSurfaceShader(WTSurfaceShader* pShader,
                        int newAlpha = 255);

private:
  WTCamera* camera = NULL;
  WTBitmap* texture = NULL;
  WTSurfaceShader* shader = NULL;
};
