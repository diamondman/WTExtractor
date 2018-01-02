#include "basetypes.hpp"
#include "WTFont.hpp"
#include "WTBitmap.hpp"

void WTFont::drawText(WTBitmap* iDstBitmap,
                      int x,
                      int y,
                      char* Text_To_Draw){
  APILOG;
}

void WTFont::setTextBold(int Draw_Text_In_Bold){
  APILOG;
}

void WTFont::setTextHeight(int Text_Height_In_Points){
  APILOG;
}

void WTFont::setTextItalic(int Draw_Text_In_Italic){
  APILOG;
}

void WTFont::setTextProperties(int Amount_Of_Bold,
                               int Draw_Text_In_Italic,
                               int Draw_Text_Underline,
                               int Draw_Text_Strikeout,
                               int Text_CharacterSet,
                               int Text_Quality){
  APILOG;
}

void WTFont::setTextFace(char* Font_Name_List){
  APILOG;
}

void WTFont::setTextColor(unsigned char Red,
                          unsigned char Green,
                          unsigned char Blue){
  APILOG;
}

void WTFont::setTextBkColor(unsigned char Red,
                            unsigned char Green,
                            unsigned char Blue){
  APILOG;
}

void WTFont::setTextUnderline(int Draw_Text_In_Underline){
  APILOG;
}

int WTFont::getTextStringWidth(char* Text_To_Measure){
  APILOG;
  return 0;
}

int WTFont::getTextStringHeight(char* Text_To_Measure){
  APILOG;
  return 0;
}

int WTFont::getTextMaxCharWidth(){
  APILOG;
  return 0;
}

int WTFont::getTextStdAscent(){
  APILOG;
  return 0;
}

int WTFont::getTextStdDescent(){
  APILOG;
  return 0;
}

int WTFont::getTextStdLeading(){
  APILOG;
  return 0;
}

int WTFont::getTextMaxAscent(){
  APILOG;
  return 0;
}

int WTFont::getTextMaxDescent(){
  APILOG;
  return 0;
}

char* WTFont::getTextFace(){
  APILOG;
  return (char*)"";
}

void WTFont::drawTextRect(WTBitmap* iDstBitmap,
                          int x,
                          int y,
                          int Width,
                          int Height,
                          char* Text_To_Draw,
                          int Flags){
  APILOG;
}
