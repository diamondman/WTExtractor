package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;
import wildtangent.webdriver.WTGroup;
import wildtangent.webdriver.WTSurfaceShader;

public interface WTString3D
extends WTGroup {
    public void setGlyphRelativeRotation(int var1, float var2, float var3, float var4, float var5);

    public void setTextFace(String var1, int var2);

    public void setGlyphRelativePosition(int var1, float var2, float var3, float var4);

    public int getTextLength();

    public void setColor(int var1, int var2, int var3, int var4);

    public void setTextureCoordScale(float var1, float var2, int var3);

    public void setSurfaceShader(WTSurfaceShader var1, int var2);

    public void setTextProperties(int var1, int var2, int var3);

    public void setTextureCoordOffset(float var1, float var2, int var3);

    public void setText(String var1);

    public void setTexture(WTBitmap var1, int var2);
}

