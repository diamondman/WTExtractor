#pragma once

#include "WTGroup.hpp"

class WTBitmap;
class WTSurfaceShader;

class WTSpout : public WTGroup {

public:
  WTSpout();

  int getObjectType(){
    APILOG;
    return this->WTGroup::getObjectType() |
      WTSPOUT;
  }

  void setTexture(WTBitmap* pBitmap);

  void setSurfaceShader(WTSurfaceShader* pISurfaceShader);

  void setRate(float Rate);

  void setScaleRange(float minScale,
                     float maxScale,
                     int unitLifePoint);

  void setParticlePropertyRange(int property,
                                float minValue,
                                float maxValue);

  void setExternalForce(float x,
                        float y,
                        float Z);

  void setColorRange(int minRed,
                     int minGreen,
                     int minBlue,
                     int minAlpha,
                     int maxRed,
                     int maxGreen,
                     int maxBlue,
                     int maxAlpha,
                     int unitLifePoint);

  void setSourcePointRange(float minValue,
                           float maxValue);

  void setMode(int mode);
};
