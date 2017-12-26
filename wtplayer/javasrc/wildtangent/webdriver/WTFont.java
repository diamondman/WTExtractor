package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;

public interface WTFont {
    public void setTextHeight(int var1);

    public void setTextFace(String var1);

    public String getTextFace();

    public void setTextItalic(int var1);

    public void drawTextRect(WTBitmap var1, int var2, int var3, int var4, int var5, String var6, int var7);

    public int getTextStdAscent();

    public int getTextStdDescent();

    public void drawTextRect(WTBitmap var1, int var2, int var3, int var4, int var5, String var6);

    public int getTextStringHeight(String var1);

    public int getTextMaxAscent();

    public int getTextMaxDescent();

    public void setTextColor(byte var1, byte var2, byte var3);

    public void setTextColor(int var1, int var2, int var3);

    public int getTextStringWidth(String var1);

    public int getTextMaxCharWidth();

    public int getTextStdLeading();

    public void setTextBkColor(byte var1, byte var2, byte var3);

    public void setTextBkColor(int var1, int var2, int var3);

    public void setTextBold(int var1);

    public void setTextProperties(int var1, int var2, int var3, int var4, int var5, int var6);

    public void setTextUnderline(int var1);

    public void drawText(WTBitmap var1, int var2, int var3, String var4);
}

