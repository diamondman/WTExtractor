#include "WTFont.hpp"
#include "WTBitmap.hpp"

void WTFont::drawText(WTBitmap* iDstBitmap,
                      int x,
                      int y,
                      char* Text_To_Draw){}

void WTFont::setTextBold(int Draw_Text_In_Bold){}

void WTFont::setTextHeight(int Text_Height_In_Points){}

void WTFont::setTextItalic(int Draw_Text_In_Italic){}

void WTFont::setTextProperties(int Amount_Of_Bold,
                               int Draw_Text_In_Italic,
                               int Draw_Text_Underline,
                               int Draw_Text_Strikeout,
                               int Text_CharacterSet,
                               int Text_Quality){}

void WTFont::setTextFace(char* Font_Name_List){}

void WTFont::setTextColor(unsigned char Red,
                          unsigned char Green,
                          unsigned char Blue){}

void WTFont::setTextBkColor(unsigned char Red,
                            unsigned char Green,
                            unsigned char Blue){}

void WTFont::setTextUnderline(int Draw_Text_In_Underline){}

int WTFont::getTextStringWidth(char* Text_To_Measure){
  return 0;
}

int WTFont::getTextStringHeight(char* Text_To_Measure){
  return 0;
}

int WTFont::getTextMaxCharWidth(){
  return 0;
}

int WTFont::getTextStdAscent(){
  return 0;
}

int WTFont::getTextStdDescent(){
  return 0;
}

int WTFont::getTextStdLeading(){
  return 0;
}

int WTFont::getTextMaxAscent(){
  return 0;
}

int WTFont::getTextMaxDescent(){
  return 0;
}

char* WTFont::getTextFace(){
  return (char*)"";
}

void WTFont::drawTextRect(WTBitmap* iDstBitmap,
                          int x,
                          int y,
                          int Width,
                          int Height,
                          char* Text_To_Draw,
                          int Flags){}
