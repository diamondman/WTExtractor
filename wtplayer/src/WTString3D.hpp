#pragma once

#include "WTGroup.hpp"

class WTBitmap;
class WTSurfaceShader;

class WTString3D : public WTGroup {

public:
  WTString3D(WT* wt_);

  int getObjectType(){
    APILOG;
    return this->WTGroup::getObjectType() |
      WTSTRING3D;
  }

  void setText(char* text);

  void setTextProperties(int drawTextInBold,
                         int drawTextInItalic,
                         int quality);

  void setColor(int Red,
                int Green,
                int Blue,
                int Alpha);

  void setTexture(WTBitmap* pBitmap,
                  int Side);

  void setTextureCoordOffset(float U1,
                             float V1,
                             int Side);

  void setTextureCoordScale(float U1,
                            float V1,
                            int Side);

  void setSurfaceShader(WTSurfaceShader* pISurfaceShader,
                        int Side);

  void setTextFace(char* fontSearchString,
                   int textCharacterSet);

  int getTextLength();

  void setGlyphRelativePosition(int glyphIndex,
                                float x,
                                float y,
                                float Z);

  void setGlyphRelativeRotation(int glyphIndex,
                                float x,
                                float y,
                                float Z,
                                float Angle);
};
