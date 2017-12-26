package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;
import wildtangent.webdriver.WTCollisionInfo;
import wildtangent.webdriver.WTContainer;
import wildtangent.webdriver.WTDrop;
import wildtangent.webdriver.WTVector3D;

public interface WTCamera
extends WTContainer {
    public WTDrop getDrop(int var1);

    public void setZoom(int var1);

    public void setViewRect(int var1, int var2, int var3, int var4);

    public WTCollisionInfo pick(int var1, int var2);

    public WTVector3D screenPointToWorldPoint(int var1, int var2, float var3);

    public int suspend(boolean var1);

    public int suspend();

    public void setClipping(float var1, float var2);

    public void setClipping(float var1);

    public WTVector3D worldPointToScreenPoint(float var1, float var2, float var3);

    public void removeDrop(WTDrop var1);

    public int resume();

    public WTDrop addDrop(WTBitmap var1, boolean var2);

    public WTDrop addDrop(WTBitmap var1);

    public void setFieldOfView(float var1);

    public void setUpdateFrequency(int var1);

    public void setRenderPriority(int var1);

    public int getRenderPriority();

    public WTBitmap getRenderBitmap();

    public int getDropCount(boolean var1);

    public int getDropCount();

    public void setBitmapClearColor(int var1, int var2, int var3);
}

