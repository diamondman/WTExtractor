#include "WTBitmap.hpp"

void WTBitmap::setColorKey(unsigned char Red,
                           unsigned char Green,
                           unsigned char Blue){}

void WTBitmap::unsetColorKey(){}

int WTBitmap::getWidth(){
  return 0;
}

int WTBitmap::getHeight(){
  return 0;
}

void WTBitmap::drawText(int x,
                        int y,
                        char* Text_To_Draw){}

void WTBitmap::setTextBold(int Draw_Text_In_Bold){}

void WTBitmap::setTextHeight(int Text_Height_In_Points){}

void WTBitmap::setTextItalic(int Draw_Text_In_Italic){}

void WTBitmap::setTextProperties(int Amount_Of_Bold,
                                 int Draw_Text_In_Italic,
                                 int Draw_Text_Underline,
                                 int Draw_Text_Strikeout,
                                 int Text_CharacterSet,
                                 int Text_Quality){}

//[id(0x00002332), hidden]
void WTBitmap::setTextFamily(int nPitch,
                             int nFamily){}

void WTBitmap::setTextFace(char* Font_Name_List){}

void WTBitmap::setTextColor(unsigned char Red,
                            unsigned char Green,
                            unsigned char Blue){}

void WTBitmap::setTextBkColor(unsigned char Red,
                              unsigned char Green,
                              unsigned char Blue){}

void WTBitmap::setColor(unsigned char Red,
                        unsigned char Green,
                        unsigned char Blue){}

void WTBitmap::drawLine(int X1,
                        int Y1,
                        int X2,
                        int Y2){}

void WTBitmap::setDrawColor(unsigned char Red,
                            unsigned char Green,
                            unsigned char Blue){}

void WTBitmap::drawPixel(int x,
                         int y){}

void WTBitmap::destroy(){}

void WTBitmap::drawFillRect(int x,
                            int y,
                            int Width,
                            int Height){}

void WTBitmap::copyRect(WTBitmap* Source_Bitmap_To_Copy_From,
                        int Type,
                        int Source_X,
                        int Source_Y,
                        int Source_Width,
                        int Source_Height,
                        int Destination_X,
                        int Destination_Y,
                        int Destination_Width,
                        int Destination_Height){}

//[id(0x0000233f), hidden]
void WTBitmap::drawLineWithString(char* str,
                                  int bPolyline){}

//[id(0x00002340), hidden]
void WTBitmap::drawPixelWithString(char* str){}

//[id(0x00002341), hidden]
void WTBitmap::drawPolygonWithString(char* str){}

void WTBitmap::copyRectFromIntArray(VARIANT Source_Array,
                                    int Blit_Type,
                                    int x,
                                    int y,
                                    int Source_Width,
                                    int Source_Height,
                                    int Destination_X,
                                    int Destination_Y,
                                    int Destination_Width,
                                    int Destination_Height,
                                    int Total_Array_Image_Width,
                                    int Total_Array_Image_Height){}

void WTBitmap::copyRectFromByteArray(VARIANT Source_Array,
                                     int Blit_Type,
                                     int x,
                                     int y,
                                     int Source_Width,
                                     int Source_Height,
                                     int Destination_X,
                                     int Destination_Y,
                                     int Destination_Width,
                                     int Destination_Height,
                                     int Total_Array_Image_Width,
                                     int Total_Array_Image_Height){}

void WTBitmap::setTextureOpacityMask(WTBitmap* Bitmap_To_Be_Used_As_Alpha_Mask,
                                     int Channel){}

void WTBitmap::enableTextureTranslucency(bool Enable_Texture_Translucency){}

void WTBitmap::mapColorToBitmap(WTBitmap* Source_Bitmap,
                                int Red,
                                int Green,
                                int Blue){}

void WTBitmap::setTextUnderline(int Draw_Text_In_Underline){}
