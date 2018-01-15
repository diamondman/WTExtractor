#pragma once

#include "WTContainer.hpp"

class WTLight : public WTContainer {

public:
  WTLight();

  WTLight(int Type);

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

  //[id(0x00001b66)]
  //void zzstub1();

  //[id(0x00001b67)]
  //void zzstub2();

  bool isStatic();

  void setLightMask(int LightMask);

  int getLightMask();
};
