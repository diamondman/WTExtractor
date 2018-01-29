#pragma once

#include "WTObject.hpp"

class WTBitmap;

class WTSurfaceShader : public WTObject {

public:
  WTSurfaceShader(WT* wt_);

  void setNumLayers(int num_layers);

  int getNumLayers();

  int getNumPasses();

  void setDepthOption(int OptionID,
                      float OptionValue);

  void setLayerSource(int LayerID,
                      int Source);

  int getLayerSource(int LayerID);

  void setLayerType(int LayerID,
                    int Type);

  int getLayerType(int LayerID);

  void setTexture(int LayerID,
                  WTBitmap* Texture_To_Use = 0);

  void setTextureCoordGenMethod(int LayerID,
                                int TexCoordGenMethod);

  int getTextureCoordGenMethod(int LayerID);

  void setTextureCoordOffsets(int LayerID,
                              float UOffset,
                              float VOffset,
                              float SOffset = 0,
                              float TOffset = 0);

  void setTextureCoordOffset(int LayerID,
                             int Coordinate,
                             float Offset);

  float getTextureCoordOffset(int LayerID,
                              int Coordinate);

  void setTextureCoordScales(int LayerID,
                             float UScale,
                             float VScale,
                             float SScale = 0,
                             float TScale = 0);

  void setTextureCoordScale(int LayerID,
                            int Coordinate,
                            float Scale);

  float getTextureCoordScale(int LayerID,
                             int Coordinate);

  void setTextureNumMipMapLevels(int LayerID,
                                 int Depth);

  int getTextureNumMipMapLevels(int LayerID);

  void setGeometryAmbientColor(unsigned char Red,
                               unsigned char Green,
                               unsigned char Blue);

  unsigned char getGeometryAmbientColorRed();

  unsigned char getGeometryAmbientColorGreen();

  unsigned char getGeometryAmbientColorBlue();

  void setGeometryAmbientOverride(bool Override);

  bool getGeometryAmbientOverride();

  void setGeometryDiffuseColor(unsigned char Red,
                               unsigned char Green,
                               unsigned char Blue,
                               unsigned char Alpha);

  unsigned char getGeometryDiffuseColorRed();

  unsigned char getGeometryDiffuseColorGreen();

  unsigned char getGeometryDiffuseColorBlue();

  unsigned char getGeometryDiffuseColorAlpha();

  void setGeometryDiffuseOverride(bool Override);

  bool getGeometryDiffuseOverride();

  void setGeometryEmissiveColor(unsigned char Red,
                                unsigned char Green,
                                unsigned char Blue);

  unsigned char getGeometryEmissiveColorRed();

  unsigned char getGeometryEmissiveColorGreen();

  unsigned char getGeometryEmissiveColorBlue();

  void setGeometryEmissiveOverride(bool Override);

  bool getGeometryEmissiveOverride();

  void setGeometrySpecularColor(unsigned char Red,
                                unsigned char Green,
                                unsigned char Blue);

  unsigned char getGeometrySpecularColorRed();

  unsigned char getGeometrySpecularColorGreen();

  unsigned char getGeometrySpecularColorBlue();

  void setGeometrySpecularPower(float Power);

  float getGeometrySpecularPower();

  void setGeometrySpecularOverride(bool Override);

  bool getGeometrySpecularOverride();

  void setProceduralWithString(int LayerID,
                               char* str);

  void setFrameBufferOperation(int FrameBufferOp);

  int getFrameBufferOperation();

  void setTextureFiltering(int LayerID,
                           bool DoFiltering);

  bool getTextureFiltering(int LayerID);

  void setLightingEnabled(bool DoLighting);

  bool getLightingEnabled();

  void setSortingOption(int Option);

  void setAlphaTestOption(bool Enable,
                          int OptionValue = 128);
};
