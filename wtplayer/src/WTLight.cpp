#include "WTLight.hpp"

void WTLight::setColor(int Red,
                       int Green,
                       int Blue){}

float WTLight::getConstantAttenuation(){
  return 0;
}

float WTLight::getLinearAttenuation(){
  return 0;
}

float WTLight::getPenumbra(){
  return 0;
}

float WTLight::getQuadraticAttenuation(){
  return 0;
}

float WTLight::getRange(){
  return 0;
}

float WTLight::getUmbra(){
  return 0;
}

void WTLight::setConstantAttenuation(float Constant_Attenuation){}

void WTLight::setLinearAttenuation(float Linear_Attenuation){}

void WTLight::setPenumbra(float Degrees){}

void WTLight::setQuadraticAttenuation(float Quadratic_Attenuation){}

void WTLight::setRange(float Range){}

void WTLight::setUmbra(float Degrees){}

bool WTLight::isStatic(){
  return 0;
}

void WTLight::setLightMask(int LightMask){}

int WTLight::getLightMask(){
  return 0;
}
