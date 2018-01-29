#include "basetypes.hpp"
#include "WTLight.hpp"

WTLight::WTLight(WT* wt_,
                 int Type) :
  WTContainer(wt_) {
}

void WTLight::setColor(int Red,
                       int Green,
                       int Blue){
  APILOG;
}

float WTLight::getConstantAttenuation(){
  APILOG;
  return 0;
}

float WTLight::getLinearAttenuation(){
  APILOG;
  return 0;
}

float WTLight::getPenumbra(){
  APILOG;
  return 0;
}

float WTLight::getQuadraticAttenuation(){
  APILOG;
  return 0;
}

float WTLight::getRange(){
  APILOG;
  return 0;
}

float WTLight::getUmbra(){
  APILOG;
  return 0;
}

void WTLight::setConstantAttenuation(float Constant_Attenuation){
  APILOG;
}

void WTLight::setLinearAttenuation(float Linear_Attenuation){
  APILOG;
}

void WTLight::setPenumbra(float Degrees){
  APILOG;
}

void WTLight::setQuadraticAttenuation(float Quadratic_Attenuation){
  APILOG;
}

void WTLight::setRange(float Range){
  APILOG;
}

void WTLight::setUmbra(float Degrees){
  APILOG;
}

bool WTLight::isStatic(){
  APILOG;
  return 0;
}

void WTLight::setLightMask(int LightMask){
  APILOG;
}

int WTLight::getLightMask(){
  APILOG;
  return 0;
}
