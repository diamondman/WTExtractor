#include "WTSurfaceShader.hpp"
#include "WTBitmap.hpp"

void WTSurfaceShader::setNumLayers(int num_layers){}

int WTSurfaceShader::getNumLayers(){
  return 0;
}

int WTSurfaceShader::getNumPasses(){
  return 0;
}

void WTSurfaceShader::setDepthOption(int OptionID,
                                     float OptionValue){}

void WTSurfaceShader::setLayerSource(int LayerID,
                                     int Source){}

int WTSurfaceShader::getLayerSource(int LayerID){
  return 0;
}

void WTSurfaceShader::setLayerType(int LayerID,
                                   int Type){}

int WTSurfaceShader::getLayerType(int LayerID){
  return 0;
}

void WTSurfaceShader::setTexture(int LayerID,
                                 WTBitmap* Texture_To_Use){}

void WTSurfaceShader::setTextureCoordGenMethod(int LayerID,
                                               int TexCoordGenMethod){}

int WTSurfaceShader::getTextureCoordGenMethod(int LayerID){
  return 0;
}

void WTSurfaceShader::setTextureCoordOffsets(int LayerID,
                                             float UOffset,
                                             float VOffset,
                                             float SOffset,
                                             float TOffset){}

void WTSurfaceShader::setTextureCoordOffset(int LayerID,
                                            int Coordinate,
                                            float Offset){}

float WTSurfaceShader::getTextureCoordOffset(int LayerID,
                                             int Coordinate){
  return 0;
}

void WTSurfaceShader::setTextureCoordScales(int LayerID,
                                            float UScale,
                                            float VScale,
                                            float SScale,
                                            float TScale){}

void WTSurfaceShader::setTextureCoordScale(int LayerID,
                                           int Coordinate,
                                           float Scale){}

float WTSurfaceShader::getTextureCoordScale(int LayerID,
                                            int Coordinate){
  return 0;
}

void WTSurfaceShader::setTextureNumMipMapLevels(int LayerID,
                                                int Depth){}

int WTSurfaceShader::getTextureNumMipMapLevels(int LayerID){
  return 0;
}

void WTSurfaceShader::setGeometryAmbientColor(unsigned char Red,
                                              unsigned char Green,
                                              unsigned char Blue){}

unsigned char WTSurfaceShader::getGeometryAmbientColorRed(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometryAmbientColorGreen(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometryAmbientColorBlue(){
  return 0;
}

void WTSurfaceShader::setGeometryAmbientOverride(bool Override){}

bool WTSurfaceShader::getGeometryAmbientOverride(){
  return 0;
}

void WTSurfaceShader::setGeometryDiffuseColor(unsigned char Red,
                                              unsigned char Green,
                                              unsigned char Blue,
                                              unsigned char Alpha){}

unsigned char WTSurfaceShader::getGeometryDiffuseColorRed(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometryDiffuseColorGreen(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometryDiffuseColorBlue(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometryDiffuseColorAlpha(){
  return 0;
}

void WTSurfaceShader::setGeometryDiffuseOverride(bool Override){}

bool WTSurfaceShader::getGeometryDiffuseOverride(){
  return 0;
}

void WTSurfaceShader::setGeometryEmissiveColor(unsigned char Red,
                                               unsigned char Green,
                                               unsigned char Blue){}

unsigned char WTSurfaceShader::getGeometryEmissiveColorRed(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometryEmissiveColorGreen(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometryEmissiveColorBlue(){
  return 0;
}

void WTSurfaceShader::setGeometryEmissiveOverride(bool Override){}

bool WTSurfaceShader::getGeometryEmissiveOverride(){
  return 0;
}

void WTSurfaceShader::setGeometrySpecularColor(unsigned char Red,
                                               unsigned char Green,
                                               unsigned char Blue){}

unsigned char WTSurfaceShader::getGeometrySpecularColorRed(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometrySpecularColorGreen(){
  return 0;
}

unsigned char WTSurfaceShader::getGeometrySpecularColorBlue(){
  return 0;
}

void WTSurfaceShader::setGeometrySpecularPower(float Power){}

float WTSurfaceShader::getGeometrySpecularPower(){
  return 0;
}

void WTSurfaceShader::setGeometrySpecularOverride(bool Override){}

bool WTSurfaceShader::getGeometrySpecularOverride(){
  return 0;
}

void WTSurfaceShader::setProceduralWithString(int LayerID,
                                              char* str){}

void WTSurfaceShader::setFrameBufferOperation(int FrameBufferOp){}

int WTSurfaceShader::getFrameBufferOperation(){
  return 0;
}

void WTSurfaceShader::setTextureFiltering(int LayerID,
                                          bool DoFiltering){}

bool WTSurfaceShader::getTextureFiltering(int LayerID){
  return 0;
}

void WTSurfaceShader::setLightingEnabled(bool DoLighting){}

bool WTSurfaceShader::getLightingEnabled(){
  return 0;
}

void WTSurfaceShader::setSortingOption(int Option){}

void WTSurfaceShader::setAlphaTestOption(bool Enable,
                                         int OptionValue){}
