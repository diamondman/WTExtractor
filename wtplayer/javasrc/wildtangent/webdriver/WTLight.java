package wildtangent.webdriver;

import wildtangent.webdriver.WTContainer;

public interface WTLight
extends WTContainer {
    public float getConstantAttenuation();

    public float getQuadraticAttenuation();

    public float getRange();

    public void setConstantAttenuation(float var1);

    public void setQuadraticAttenuation(float var1);

    public void setRange(float var1);

    public boolean isStatic();

    public float getPenumbra();

    public float getUmbra();

    public void setColor(int var1, int var2, int var3);

    public void setPenumbra(float var1);

    public void setUmbra(float var1);

    public float getLinearAttenuation();

    public void setLinearAttenuation(float var1);

    public void setLightMask(int var1);

    public int getLightMask();
}

