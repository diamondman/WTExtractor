#include "basetypes.hpp"

#include "WTSurfaceShader.hpp"
#include "WTBitmap.hpp"

WTSurfaceShader::WTSurfaceShader(WT* wt_) :
  WTObject(wt_) {
}

void WTSurfaceShader::setNumLayers(int num_layers){
  APILOG;
}

int WTSurfaceShader::getNumLayers(){
  APILOG;
  return 0;
}

int WTSurfaceShader::getNumPasses(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setDepthOption(int OptionID,
                                     float OptionValue){
  APILOG;
}

void WTSurfaceShader::setLayerSource(int LayerID,
                                     int Source){
  APILOG;
}

int WTSurfaceShader::getLayerSource(int LayerID){
  APILOG;
  return 0;
}

void WTSurfaceShader::setLayerType(int LayerID,
                                   int Type){
  APILOG;
}

int WTSurfaceShader::getLayerType(int LayerID){
  APILOG;
  return 0;
}

void WTSurfaceShader::setTexture(int LayerID,
                                 WTBitmap* Texture_To_Use){
  APILOG;
}

void WTSurfaceShader::setTextureCoordGenMethod(int LayerID,
                                               int TexCoordGenMethod){
  APILOG;
}

int WTSurfaceShader::getTextureCoordGenMethod(int LayerID){
  APILOG;
  return 0;
}

void WTSurfaceShader::setTextureCoordOffsets(int LayerID,
                                             float UOffset,
                                             float VOffset,
                                             float SOffset,
                                             float TOffset){
  APILOG;
}

void WTSurfaceShader::setTextureCoordOffset(int LayerID,
                                            int Coordinate,
                                            float Offset){
  APILOG;
}

float WTSurfaceShader::getTextureCoordOffset(int LayerID,
                                             int Coordinate){
  APILOG;
  return 0;
}

void WTSurfaceShader::setTextureCoordScales(int LayerID,
                                            float UScale,
                                            float VScale,
                                            float SScale,
                                            float TScale){
  APILOG;
}

void WTSurfaceShader::setTextureCoordScale(int LayerID,
                                           int Coordinate,
                                           float Scale){
  APILOG;
}

float WTSurfaceShader::getTextureCoordScale(int LayerID,
                                            int Coordinate){
  APILOG;
  return 0;
}

void WTSurfaceShader::setTextureNumMipMapLevels(int LayerID,
                                                int Depth){
  APILOG;
}

int WTSurfaceShader::getTextureNumMipMapLevels(int LayerID){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometryAmbientColor(unsigned char Red,
                                              unsigned char Green,
                                              unsigned char Blue){
  APILOG;
}

unsigned char WTSurfaceShader::getGeometryAmbientColorRed(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometryAmbientColorGreen(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometryAmbientColorBlue(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometryAmbientOverride(bool Override){
  APILOG;
}

bool WTSurfaceShader::getGeometryAmbientOverride(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometryDiffuseColor(unsigned char Red,
                                              unsigned char Green,
                                              unsigned char Blue,
                                              unsigned char Alpha){
  APILOG;
}

unsigned char WTSurfaceShader::getGeometryDiffuseColorRed(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometryDiffuseColorGreen(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometryDiffuseColorBlue(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometryDiffuseColorAlpha(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometryDiffuseOverride(bool Override){
  APILOG;
}

bool WTSurfaceShader::getGeometryDiffuseOverride(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometryEmissiveColor(unsigned char Red,
                                               unsigned char Green,
                                               unsigned char Blue){
  APILOG;
}

unsigned char WTSurfaceShader::getGeometryEmissiveColorRed(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometryEmissiveColorGreen(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometryEmissiveColorBlue(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometryEmissiveOverride(bool Override){
  APILOG;
}

bool WTSurfaceShader::getGeometryEmissiveOverride(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometrySpecularColor(unsigned char Red,
                                               unsigned char Green,
                                               unsigned char Blue){
  APILOG;
}

unsigned char WTSurfaceShader::getGeometrySpecularColorRed(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometrySpecularColorGreen(){
  APILOG;
  return 0;
}

unsigned char WTSurfaceShader::getGeometrySpecularColorBlue(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometrySpecularPower(float Power){
  APILOG;
}

float WTSurfaceShader::getGeometrySpecularPower(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setGeometrySpecularOverride(bool Override){
  APILOG;
}

bool WTSurfaceShader::getGeometrySpecularOverride(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setProceduralWithString(int LayerID,
                                              char* str){
  APILOG;
}

void WTSurfaceShader::setFrameBufferOperation(int FrameBufferOp){
  APILOG;
}

int WTSurfaceShader::getFrameBufferOperation(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setTextureFiltering(int LayerID,
                                          bool DoFiltering){
  APILOG;
}

bool WTSurfaceShader::getTextureFiltering(int LayerID){
  APILOG;
  return 0;
}

void WTSurfaceShader::setLightingEnabled(bool DoLighting){
  APILOG;
}

bool WTSurfaceShader::getLightingEnabled(){
  APILOG;
  return 0;
}

void WTSurfaceShader::setSortingOption(int Option){
  APILOG;
}

void WTSurfaceShader::setAlphaTestOption(bool Enable,
                                         int OptionValue){
  APILOG;
}
