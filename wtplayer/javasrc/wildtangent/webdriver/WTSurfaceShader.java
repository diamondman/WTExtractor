package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;
import wildtangent.webdriver.WTObject;

public interface WTSurfaceShader
extends WTObject {
    public void setTextureCoordOffsets(int var1, float var2, float var3, float var4, float var5);

    public void setTextureCoordOffsets(int var1, float var2, float var3, float var4);

    public void setTextureCoordGenMethod(int var1, int var2);

    public int getTextureCoordGenMethod(int var1);

    public void setTextureCoordOffsets(int var1, float var2, float var3);

    public void setGeometryDiffuseOverride(boolean var1);

    public boolean getGeometryDiffuseOverride();

    public void setGeometryEmissiveOverride(boolean var1);

    public boolean getGeometryEmissiveOverride();

    public void setDepthOption(int var1, float var2);

    public void setFrameBufferOperation(int var1);

    public int getFrameBufferOperation();

    public void setAlphaTestOption(boolean var1, int var2);

    public void setAlphaTestOption(boolean var1);

    public void setGeometryAmbientColor(byte var1, byte var2, byte var3);

    public void setGeometryAmbientColor(int var1, int var2, int var3);

    public void setGeometrySpecularColor(byte var1, byte var2, byte var3);

    public void setGeometrySpecularColor(int var1, int var2, int var3);

    public void setGeometryDiffuseColor(byte var1, byte var2, byte var3, byte var4);

    public void setGeometryDiffuseColor(int var1, int var2, int var3, int var4);

    public void setGeometryEmissiveColor(byte var1, byte var2, byte var3);

    public void setGeometryEmissiveColor(int var1, int var2, int var3);

    public void setGeometrySpecularPower(float var1);

    public float getGeometrySpecularPower();

    public void setTextureFiltering(int var1, boolean var2);

    public boolean getTextureFiltering(int var1);

    public byte getGeometryDiffuseColorAlpha();

    public int getNumPasses();

    public void setLightingEnabled(boolean var1);

    public boolean getLightingEnabled();

    public void setTextureCoordScale(int var1, int var2, float var3);

    public float getTextureCoordScale(int var1, int var2);

    public void setTextureNumMipMapLevels(int var1, int var2);

    public int getTextureNumMipMapLevels(int var1);

    public void setLayerSource(int var1, int var2);

    public int getLayerSource(int var1);

    public byte getGeometryAmbientColorGreen();

    public byte getGeometrySpecularColorGreen();

    public void setTexture(int var1, WTBitmap var2);

    public void setSortingOption(int var1);

    public void setTexture(int var1);

    public void setTextureCoordScales(int var1, float var2, float var3, float var4, float var5);

    public void setTextureCoordScales(int var1, float var2, float var3, float var4);

    public void setTextureCoordScales(int var1, float var2, float var3);

    public byte getGeometryDiffuseColorGreen();

    public byte getGeometryEmissiveColorGreen();

    public byte getGeometryAmbientColorRed();

    public byte getGeometrySpecularColorRed();

    public void setLayerType(int var1, int var2);

    public int getLayerType(int var1);

    public byte getGeometryAmbientColorBlue();

    public byte getGeometrySpecularColorBlue();

    public void setTextureCoordOffset(int var1, int var2, float var3);

    public float getTextureCoordOffset(int var1, int var2);

    public byte getGeometryDiffuseColorRed();

    public byte getGeometryEmissiveColorRed();

    public void setNumLayers(int var1);

    public int getNumLayers();

    public void setProceduralWithString(int var1, String var2);

    public byte getGeometryDiffuseColorBlue();

    public byte getGeometryEmissiveColorBlue();

    public void setGeometryAmbientOverride(boolean var1);

    public boolean getGeometryAmbientOverride();

    public void setGeometrySpecularOverride(boolean var1);

    public boolean getGeometrySpecularOverride();
}

