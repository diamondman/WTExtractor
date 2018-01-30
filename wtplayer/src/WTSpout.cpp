#include "basetypes.hpp"
#include "WTSpout.hpp"
#include "WTBitmap.hpp"
#include "WTSurfaceShader.hpp"

WTSpout::WTSpout(WT* wt_) :
  WTGroup(wt_) {
}

WTSpout::~WTSpout() {
  if(this->shader)
    this->shader->Release();
  this->shader = NULL;

  if(this->texture)
    this->texture->Release();
  this->texture = NULL;
}

void WTSpout::setTexture(WTBitmap* pBitmap){
  APILOG;
  if(this->texture)
    this->texture->Release();
  this->texture = pBitmap;
  this->texture->AddRef();
}

void WTSpout::setSurfaceShader(WTSurfaceShader* pISurfaceShader){
  APILOG;
  if(this->shader)
    this->shader->Release();
  this->shader = pISurfaceShader;
  this->shader->AddRef();
}

void WTSpout::setRate(float Rate){
  APILOG;
}

void WTSpout::setScaleRange(float minScale,
                            float maxScale,
                            int unitLifePoint){
  APILOG;
}

void WTSpout::setParticlePropertyRange(int property,
                                       float minValue,
                                       float maxValue){
  APILOG;
}

void WTSpout::setExternalForce(float x,
                               float y,
                               float Z){
  APILOG;
}

void WTSpout::setColorRange(int minRed,
                            int minGreen,
                            int minBlue,
                            int minAlpha,
                            int maxRed,
                            int maxGreen,
                            int maxBlue,
                            int maxAlpha,
                            int unitLifePoint){
  APILOG;
}

void WTSpout::setSourcePointRange(float minValue,
                                  float maxValue){
  APILOG;
}

void WTSpout::setMode(int mode){
  APILOG;
}
