package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;
import wildtangent.webdriver.WTCamera;
import wildtangent.webdriver.WTGroup;
import wildtangent.webdriver.WTSurfaceShader;

public interface WTPortal
extends WTGroup {
    public void setMappingOption(int var1);

    public void setTexture(WTBitmap var1);

    public void setCustomTransform(int var1, float var2, float var3, float var4);

    public void setDoubleSided(boolean var1);

    public void setSurfaceShader(WTSurfaceShader var1, int var2);

    public void setSurfaceShader(WTSurfaceShader var1);

    public void setRenderOnlyChildren(boolean var1);

    public void setCamera(WTCamera var1);

    public WTCamera getCamera();

    public void setTexture(WTBitmap var1, int var2);

    public void setMappingOption(int var1, float var2);
}

