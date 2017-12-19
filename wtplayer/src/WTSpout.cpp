#include "WTSpout.hpp"
#include "WTBitmap.hpp"
#include "WTSurfaceShader.hpp"

void WTSpout::setTexture(WTBitmap* pBitmap){}

void WTSpout::setSurfaceShader(WTSurfaceShader* pISurfaceShader){}

void WTSpout::setRate(float Rate){}

void WTSpout::setScaleRange(float minScale,
                            float maxScale,
                            int unitLifePoint){}

void WTSpout::setParticlePropertyRange(int property,
                                       float minValue,
                                       float maxValue){}

void WTSpout::setExternalForce(float x,
                               float y,
                               float Z){}

void WTSpout::setColorRange(int minRed,
                            int minGreen,
                            int minBlue,
                            int minAlpha,
                            int maxRed,
                            int maxGreen,
                            int maxBlue,
                            int maxAlpha,
                            int unitLifePoint){}

void WTSpout::setSourcePointRange(float minValue,
                                  float maxValue){}

void WTSpout::setMode(int mode){}
