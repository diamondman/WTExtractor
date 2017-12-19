#pragma once

class WTBitmap;

class WTFont {

public:
  void drawText(WTBitmap* iDstBitmap,
                int x,
                int y,
                char* Text_To_Draw);

  void setTextBold(int Draw_Text_In_Bold);

  void setTextHeight(int Text_Height_In_Points);

  void setTextItalic(int Draw_Text_In_Italic);

  void setTextProperties(int Amount_Of_Bold,
                         int Draw_Text_In_Italic,
                         int Draw_Text_Underline,
                         int Draw_Text_Strikeout,
                         int Text_CharacterSet,
                         int Text_Quality);

  void setTextFace(char* Font_Name_List);

  void setTextColor(unsigned char Red,
                    unsigned char Green,
                    unsigned char Blue);

  void setTextBkColor(unsigned char Red,
                      unsigned char Green,
                      unsigned char Blue);

  void setTextUnderline(int Draw_Text_In_Underline);

  int getTextStringWidth(char* Text_To_Measure);

  int getTextStringHeight(char* Text_To_Measure);

  int getTextMaxCharWidth();

  int getTextStdAscent();

  int getTextStdDescent();

  int getTextStdLeading();

  int getTextMaxAscent();

  int getTextMaxDescent();

  char* getTextFace();

  void drawTextRect(WTBitmap* iDstBitmap,
                    int x,
                    int y,
                    int Width,
                    int Height,
                    char* Text_To_Draw,
                    int Flags = 0);
};
