package wildtangent.webdriver;

import wildtangent.webdriver.WTGroup;

public interface WTShadow
extends WTGroup {
    public void setRange(boolean var1, float var2, float var3);

    public void setRange(boolean var1, float var2);

    public void setRange(boolean var1);

    public int getCasterColorRed(WTGroup var1);

    public void enableCulling(boolean var1, boolean var2);

    public void setResolution(int var1, int var2);

    public int getCasterColorBlue(WTGroup var1);

    public void setCasterColor(WTGroup var1, int var2, int var3, int var4);

    public void setFieldOfView(float var1);

    public float getFieldOfView();

    public void setFiltering(int var1);

    public int getFiltering();

    public void setEnable(boolean var1);

    public boolean getEnable();

    public void removeCaster(WTGroup var1);

    public void removeReceiver(WTGroup var1);

    public int getType();

    public int getHeight();

    public void addCaster(WTGroup var1, int var2, int var3, int var4);

    public void addCaster(WTGroup var1, int var2, int var3);

    public void addCaster(WTGroup var1, int var2);

    public void addCaster(WTGroup var1);

    public void addReceiver(WTGroup var1);

    public int getCasterColorGreen(WTGroup var1);

    public int getWidth();
}

