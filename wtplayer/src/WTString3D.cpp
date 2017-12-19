#include "WTString3D.hpp"
#include "WTBitmap.hpp"
#include "WTSurfaceShader.hpp"

void WTString3D::setText(char* text){}

void WTString3D::setTextProperties(int drawTextInBold,
                                   int drawTextInItalic,
                                   int quality){}

void WTString3D::setColor(int Red,
                          int Green,
                          int Blue,
                          int Alpha){}

void WTString3D::setTexture(WTBitmap* pBitmap,
                            int Side){}

void WTString3D::setTextureCoordOffset(float U1,
                                       float V1,
                                       int Side){}

void WTString3D::setTextureCoordScale(float U1,
                                      float V1,
                                      int Side){}

void WTString3D::setSurfaceShader(WTSurfaceShader* pISurfaceShader,
                                  int Side){}

void WTString3D::setTextFace(char* fontSearchString,
                             int textCharacterSet){}

int WTString3D::getTextLength(){
  return 0;
}

void WTString3D::setGlyphRelativePosition(int glyphIndex,
                                          float x,
                                          float y,
                                          float Z){}

void WTString3D::setGlyphRelativeRotation(int glyphIndex,
                                          float x,
                                          float y,
                                          float Z,
                                          float Angle){}
