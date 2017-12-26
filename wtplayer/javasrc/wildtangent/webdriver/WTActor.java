package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;
import wildtangent.webdriver.WTGroup;
import wildtangent.webdriver.WTSurfaceShader;

public interface WTActor
extends WTGroup {
    public void playMotion(String var1, int var2, int var3, float var4, float var5);

    public void playMotion(String var1, int var2, int var3, float var4);

    public void playMotion(String var1, int var2, int var3);

    public void playMotion(String var1, int var2);

    public void playMotion(String var1);

    public void setTexture(WTBitmap var1, String var2);

    public String getMotionName(int var1);

    public int getPlayingMotion(int var1);

    public String getNextMotionNote();

    public void setMotionSpeed(float var1);

    public float getMotionLength(String var1);

    public void setLODMax(float var1);

    public float getLODMax();

    public String getMaterialName(int var1);

    public int getPartCount();

    public float getPlayingMotionTime(int var1);

    public void blendMotion(String var1, float var2, float var3, float var4, float var5, float var6, int var7, int var8, float var9);

    public void blendMotion(String var1, float var2, float var3, float var4, float var5, float var6, int var7, int var8);

    public void blendMotion(String var1, float var2, float var3, float var4, float var5, float var6, int var7);

    public void blendMotion(String var1, float var2, float var3, float var4, float var5, float var6);

    public int getMotionCount();

    public int getMotionNoteCount(int var1, float var2, float var3);

    public void removeMaterial(String var1);

    public void removeMaterial();

    public int getMaterialCount();

    public void removeTexture(String var1);

    public void setColor(int var1, int var2, int var3);

    public void removeTexture();

    public float getBlendAmount(int var1);

    public int getPlayingMotionCount();

    public String getMotionNote(int var1, int var2, float var3, float var4);

    public String getPartName(int var1);

    public void setOpacity(int var1);

    public float getMotionNoteTime(int var1, int var2, float var3, float var4);

    public void setCollisionLOD(float var1);

    public float getCollisionLOD();

    public void setSurfaceShader(WTSurfaceShader var1, String var2);

    public void setSurfaceShader(WTSurfaceShader var1);

    public void stopMotion(String var1);

    public void stopMotion();

    public void setLODQuality(float var1);

    public float getLODQuality();

    public void setLightMask(int var1);

    public int getLightMask();

    public void setMaterial(WTBitmap var1, String var2);

    public void setMaterial(WTBitmap var1);

    public void setTexture(WTBitmap var1);

    public void playMotion(String var1, int var2, int var3, float var4, float var5, float var6);
}

