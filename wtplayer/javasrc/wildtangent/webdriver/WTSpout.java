package wildtangent.webdriver;

public interface WTSpout
extends WTGroup {
    public void setSourcePointRange(float var1, float var2);

    public void setRate(float var1);

    public void setMode(int var1);

    public void setExternalForce(float var1, float var2, float var3);

    public void setParticlePropertyRange(int var1, float var2, float var3);

    public void setSurfaceShader(WTSurfaceShader var1);

    public void setScaleRange(float var1, float var2, int var3);

    public void setColorRange(int var1, int var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9);

    public void setTexture(WTBitmap var1);
}

