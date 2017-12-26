package wildtangent.webdriver;

import wildtangent.webdriver.WTCamera;
import wildtangent.webdriver.WTContainer;
import wildtangent.webdriver.WTObject;

public interface WTStage
extends WTObject {
    public void removeObject(WTContainer var1);

    public float getFogEndDistance();

    public void setFogEndDistance(float var1);

    public WTCamera createCamera();

    public WTCamera createBitmapCamera(int var1, int var2);

    public void setBGColor(byte var1, byte var2, byte var3);

    public void setBGColor(int var1, int var2, int var3);

    public WTObject getChildByIndex(int var1);

    public WTObject getObjectByName(String var1, int var2);

    public WTObject getObjectByName(String var1);

    public void addObject(WTContainer var1);

    public float getFogStartDistance();

    public void setFogStartDistance(float var1);

    public int getChildCount();

    public boolean getFogEnabled();

    public void setFogEnabled(boolean var1);

    public float getFogDensity();

    public void setFogDensity(float var1);

    public void setFogColor(byte var1, byte var2, byte var3);

    public void setFogColor(int var1, int var2, int var3);
}

