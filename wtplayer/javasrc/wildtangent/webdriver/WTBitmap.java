package wildtangent.webdriver;

import wildtangent.webdriver.WTObject;

public interface WTBitmap
extends WTObject {
    public void drawLine(int var1, int var2, int var3, int var4);

    public void drawFillRect(int var1, int var2, int var3, int var4);

    public void setTextColor(byte var1, byte var2, byte var3);

    public void setTextColor(int var1, int var2, int var3);

    public void setDrawColor(byte var1, byte var2, byte var3);

    public void setDrawColor(int var1, int var2, int var3);

    public void setTextBkColor(byte var1, byte var2, byte var3);

    public void setTextBkColor(int var1, int var2, int var3);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11, int var12);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5, int var6, int var7);

    public void setTextFamily(int var1, int var2);

    public void drawPixel(int var1, int var2);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5, int var6);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4, int var5);

    public void copyRectFromIntArray(int[] var1, int var2, int var3, int var4);

    public void copyRectFromIntArray(int[] var1, int var2, int var3);

    public void copyRectFromIntArray(int[] var1, int var2);

    public void copyRectFromIntArray(int[] var1);

    public void setTextFace(String var1);

    public void unsetColorKey();

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11, int var12);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10, int var11);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5, int var6, int var7);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5, int var6);

    public void drawLineWithString(String var1, int var2);

    public void drawLineWithString(String var1);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4, int var5);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3, int var4);

    public void copyRectFromByteArray(byte[] var1, int var2, int var3);

    public void copyRectFromByteArray(byte[] var1, int var2);

    public void copyRectFromByteArray(byte[] var1);

    public void destroy();

    public void setColorKey(byte var1, byte var2, byte var3);

    public void setColorKey(int var1, int var2, int var3);

    public void setTextBold(int var1);

    public int getHeight();

    public void copyRect(WTBitmap var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10);

    public void copyRect(WTBitmap var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8);

    public void copyRect(WTBitmap var1, int var2, int var3, int var4, int var5, int var6, int var7);

    public void copyRect(WTBitmap var1, int var2, int var3, int var4, int var5, int var6);

    public void copyRect(WTBitmap var1, int var2, int var3, int var4, int var5);

    public void copyRect(WTBitmap var1, int var2, int var3, int var4);

    public void copyRect(WTBitmap var1, int var2, int var3);

    public void copyRect(WTBitmap var1, int var2);

    public void setTextItalic(int var1);

    public void copyRect(WTBitmap var1);

    public void copyRect(WTBitmap var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9);

    public void drawPolygonWithString(String var1);

    public void setTextProperties(int var1, int var2, int var3, int var4, int var5, int var6);

    public void setTextProperties(int var1, int var2, int var3, int var4, int var5);

    public void setTextProperties(int var1, int var2, int var3, int var4);

    public void setTextProperties(int var1, int var2, int var3);

    public void setTextProperties(int var1, int var2);

    public void setTextProperties(int var1);

    public int getWidth();

    public void setTextProperties();

    public void setTextHeight(int var1);

    public void setTextureOpacityMask(WTBitmap var1, int var2);

    public void setTextureOpacityMask(WTBitmap var1);

    public void setColor(byte var1, byte var2, byte var3);

    public void setColor(int var1, int var2, int var3);

    public void enableTextureTranslucency(boolean var1);

    public void drawPixelWithString(String var1);

    public void mapColorToBitmap(WTBitmap var1, int var2, int var3, int var4);

    public void setTextUnderline(int var1);

    public void drawText(int var1, int var2, String var3);
}

