package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;
import wildtangent.webdriver.WTObject;

public interface WTDrop
extends WTObject {
    public WTDrop getDrop(int var1);

    //public void stubFunction(int var1);

    public int getX();

    public void setTextureRect(float var1, float var2, float var3, float var4);

    public void bringToFront();

    public void removeDrop(WTDrop var1);

    public void setVisible(boolean var1);

    public WTDrop addDrop(WTBitmap var1, int var2);

    public WTDrop addDrop(WTBitmap var1);

    public void setOpacity(int var1);

    public void attach(WTBitmap var1);

    public WTBitmap getBitmap();

    public void setFiltering(boolean var1);

    public void setFiltering();

    public int getY();

    public void setZOrder(int var1);

    public void setPosition(int var1, int var2);

    public int getHeight();

    public int getBitmapHeight();

    public void setSize(int var1, int var2);

    public void sendToBack();

    public void detach();

    public int getDropCount();

    public void make3d(boolean var1);

    public void make3d();

    public int getWidth();

    public int getBitmapWidth();
}

