#pragma once

#include "WTContainer.hpp"

class WTLight : public WTContainer {

public:
  WTLight(WT* wt_,
          int Type);

  int getObjectType(){
    APILOG;
    return WTContainer::getObjectType() |
      WT_3D |
      WTLIGHT;
  }

  void setColor(int Red,
                int Green,
                int Blue);

  float getConstantAttenuation();

  float getLinearAttenuation();

  float getPenumbra();

  float getQuadraticAttenuation();

  float getRange();

  float getUmbra();

  void setConstantAttenuation(float Constant_Attenuation);

  void setLinearAttenuation(float Linear_Attenuation);

  void setPenumbra(float Degrees);

  void setQuadraticAttenuation(float Quadratic_Attenuation);

  void setRange(float Range);

  void setUmbra(float Degrees);

  bool isStatic();

  void setLightMask(int LightMask);

  int getLightMask();
};
