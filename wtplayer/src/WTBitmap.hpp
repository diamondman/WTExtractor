#pragma once

#include "WTObject.hpp"

class WT;

class WTBitmap : public WTObject {

  friend class WTDrop;

public:
  WTBitmap(WT* wt_,
           int width,
           int height);

  WTBitmap(WT* wt_,
           char* File_Name,
           int WTCache_Type);

  virtual ~WTBitmap();

  int getObjectType(){
    APILOG;
    return this->WTObject::getObjectType() |
      WTBITMAP;
  }

  virtual WTObject* getOwner(){
    APILOG;
    return NULL;
  }

  void setColorKey(unsigned char Red,
                   unsigned char Green,
                   unsigned char Blue);

  void unsetColorKey();

  int getWidth(){
    APILOG;
    return this->width;
  }

  int getHeight(){
    APILOG;
    return this->height;
  }

  void drawText(int x,
                int y,
                char* Text_To_Draw);

  void setTextBold(int Draw_Text_In_Bold);

  void setTextHeight(int Text_Height_In_Points);

  void setTextItalic(int Draw_Text_In_Italic);

  void setTextProperties(int Amount_Of_Bold = -999999,
                         int Draw_Text_In_Italic = -999999,
                         int Draw_Text_Underline = -999999,
                         int Draw_Text_Strikeout = -999999,
                         int Text_CharacterSet = -999999,
                         int Text_Quality = -999999);

  //[id(0x00002332), hidden]
  void setTextFamily(int nPitch,
                     int nFamily);

  void setTextFace(char* Font_Name_List);

  void setTextColor(unsigned char Red,
                    unsigned char Green,
                    unsigned char Blue);

  void setTextBkColor(unsigned char Red,
                      unsigned char Green,
                      unsigned char Blue);

  void setColor(unsigned char Red,
                unsigned char Green,
                unsigned char Blue);

  void drawLine(int X1,
                int Y1,
                int X2,
                int Y2);

  void setDrawColor(unsigned char Red,
                    unsigned char Green,
                    unsigned char Blue);

  void drawPixel(int x,
                 int y);

  void destroy();

  void drawFillRect(int x,
                    int y,
                    int Width,
                    int Height);

  void copyRect(WTBitmap* Source_Bitmap_To_Copy_From,
                int Type = 0,
                int Source_X = -1,
                int Source_Y = -1,
                int Source_Width = -1,
                int Source_Height = -1,
                int Destination_X = -1,
                int Destination_Y = -1,
                int Destination_Width = -1,
                int Destination_Height = -1);

  //[id(0x0000233f), hidden]
  void drawLineWithString(char* str,
                          int bPolyline = 0);

  //[id(0x00002340), hidden]
  void drawPixelWithString(char* str);

  //[id(0x00002341), hidden]
  void drawPolygonWithString(char* str);

  void copyRectFromIntArray(int Source_Array[],
                            int Blit_Type = -1,
                            int x = -1,
                            int y = -1,
                            int Source_Width = -1,
                            int Source_Height = -1,
                            int Destination_X = -1,
                            int Destination_Y = -1,
                            int Destination_Width = -1,
                            int Destination_Height = -1,
                            int Total_Array_Image_Width = -1,
                            int Total_Array_Image_Height = -1);

  void copyRectFromByteArray(uint8_t Source_Array[],
                             int Blit_Type = -1,
                             int x = -1,
                             int y = 20,
                             int Source_Width = -1,
                             int Source_Height = -1,
                             int Destination_X = -1,
                             int Destination_Y = -1,
                             int Destination_Width = -1,
                             int Destination_Height = -1,
                             int Total_Array_Image_Width = -1,
                             int Total_Array_Image_Height = -1);

  void setTextureOpacityMask(WTBitmap* Bitmap_To_Be_Used_As_Alpha_Mask,
                             int Channel = 0);

  void enableTextureTranslucency(bool Enable_Texture_Translucency);

  void mapColorToBitmap(WTBitmap* Source_Bitmap,
                        int Red,
                        int Green,
                        int Blue);

  void setTextUnderline(int Draw_Text_In_Underline);

private:
  typedef struct SDL_Surface SDL_Surface;
  SDL_Surface *sdlsurf = NULL;
  typedef struct _cairo_surface cairo_surface_t;
  cairo_surface_t *cairosurf;
  typedef struct _cairo cairo_t;
  cairo_t *cr;

  int text_height = 10;

  bool using_colorkey = false;
  float colorkey_r = 0;
  float colorkey_g = 0;
  float colorkey_b = 0;

  float text_r = 0;
  float text_g = 0;
  float text_b = 0;

  float text_bg_r = 0;
  float text_bg_g = 0;
  float text_bg_b = 0;

  float draw_r = 0;
  float draw_g = 0;
  float draw_b = 0;

  unsigned int width = 0;
  unsigned int height = 0;

  unsigned char *data = 0;
};
