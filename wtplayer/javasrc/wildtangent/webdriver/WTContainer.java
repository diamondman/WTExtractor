package wildtangent.webdriver;

import wildtangent.webdriver.WTCollisionInfo;
import wildtangent.webdriver.WTObject;
import wildtangent.webdriver.WTOrientation3D;
import wildtangent.webdriver.WTSurfaceShader;
import wildtangent.webdriver.WTVector3D;

public interface WTContainer
extends WTObject {
    public void setOrientation(float var1, float var2, float var3, float var4);

    public void setBitmapOrientation(float var1);

    public void unsetLookAt();

    public boolean isHighlighted();

    public void setCollisionBox(float var1, float var2, float var3, float var4, float var5, float var6, int var7);

    public void setCollisionBox(float var1, float var2, float var3, float var4, float var5, float var6);

    public String getOrientationUpAsString();

    public void setRotation(float var1, float var2, float var3, float var4, int var5);

    public void setRotation(float var1, float var2, float var3, float var4);

    public void setAbsoluteOrientation(float var1, float var2, float var3, float var4);

    public WTCollisionInfo checkCollision(float var1, float var2, float var3, boolean var4, int var5, int var6, int var7, int var8);

    public void attach(WTObject var1);

    public WTCollisionInfo checkCollision(float var1, float var2, float var3, boolean var4, int var5, int var6, int var7);

    public WTCollisionInfo checkCollision(float var1, float var2, float var3, boolean var4, int var5, int var6);

    public WTCollisionInfo checkCollision(float var1, float var2, float var3, boolean var4, int var5);

    public void attachBitmap(WTObject var1, float var2, float var3, int var4, int var5);

    public void makeCollisionBox(int var1, int var2, int var3);

    public void makeCollisionBox(int var1, int var2);

    public void makeCollisionBox(int var1);

    public void makeCollisionBox();

    public WTVector3D getOrientationVector();

    public void setOrientationVector(float var1, float var2, float var3, float var4, float var5, float var6);

    public void moveBy(float var1, float var2, float var3);

    public void setBitmapSize(float var1, float var2);

    public void setPickPriority(int var1);

    public WTObject getAttached();

    public int getPickPriority();

    public WTVector3D getOrientationUp();

    public void setAbsoluteScale(float var1);

    public void setAbsoluteScale(float var1, float var2, float var3);

    public void setAbsolutePosition(float var1, float var2, float var3);

    public WTVector3D getAbsolutePosition();

    public void setConstantRotation(float var1, float var2, float var3, float var4);

    public WTOrientation3D getConstantRotation();

    public void setBitmapTextureRect(float var1, float var2, float var3, float var4);

    public String getPositionAsString();

    public void setLookAt(WTContainer var1, int var2);

    public void setLookAt(WTContainer var1);

    public WTContainer getLookAt();

    public String getOrientationVectorAsString();

    public WTVector3D getAbsoluteOrientationVector();

    public WTVector3D getAbsoluteOrientationUp();

    public void setScale(float var1, float var2, float var3);

    public void setScale(float var1);

    public void setVisible(boolean var1);

    public boolean getVisible();

    public void setAbsoluteOrientationVector(float var1, float var2, float var3, float var4, float var5, float var6);

    public void setCollisionMask(int var1, int var2);

    public void setBitmapOpacity(int var1);

    public void setCollisionMask(int var1);

    public int getCollisionMask();

    public String getAbsolutePositionAsString();

    public void attachSurfaceShader(WTSurfaceShader var1, float var2, float var3, int var4, int var5);

    public WTVector3D getGeometryExtents(boolean var1, boolean var2);

    public void setPosition(float var1, float var2, float var3);

    public WTVector3D getPosition();

    public void highlight(boolean var1);

    public WTVector3D getGeometryExtents(boolean var1);

    public void detach();

    public void setScaleTare();

    public WTOrientation3D getOrientation();
}

