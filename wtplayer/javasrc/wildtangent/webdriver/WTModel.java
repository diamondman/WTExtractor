package wildtangent.webdriver;

import wildtangent.webdriver.WTBitmap;
import wildtangent.webdriver.WTObject;
import wildtangent.webdriver.WTSurfaceShader;
import wildtangent.webdriver.WTVector3D;

public interface WTModel
extends WTObject {
    public void setDxAnimationTime(float var1, int var2);

    public void setDxAnimationTime(float var1);

    public void setPatchPtHeight(int var1, int var2, int var3, int var4);

    public void setPatchPtHeight(int var1, int var2, int var3);

    public int addVertex(float var1, float var2, float var3);

    public void setPatchAreaUV(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8, String var9);

    public void setPatchAreaUV(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8);

    public int removeFaces(int[] var1);

    public int removeFace(int var1);

    public void setVerticesUVs(int[] var1, float[] var2, int var3, int var4, int var5);

    public void setVerticesUVs(int[] var1, float[] var2, int var3, int var4);

    public void setVerticesUVs(int[] var1, float[] var2, int var3);

    public void setVerticesUVs(int[] var1, float[] var2);

    public void setLightMask(int var1);

    public int getLightMask();

    public int getVertexCount();

    public void setPatchPtNormal(int var1, int var2, float var3, float var4, float var5, int var6);

    public void setPatchPtNormal(int var1, int var2, float var3, float var4, float var5);

    public void setFaceNormal(int var1, float var2, float var3, float var4);

    public void setTexture(WTBitmap var1, String var2);

    public void setTexture(WTBitmap var1);

    public void setPatchTileTexture(int var1, int var2, WTBitmap var3, String var4);

    public void setPatchTileTexture(int var1, int var2, WTBitmap var3);

    public void setScaleTare();

    public void setTexture(WTBitmap var1, String var2, int var3);

    public void sweep(float var1, float var2, int var3, float var4, float var5, float var6, float var7, float var8, float var9, boolean var10, boolean var11);

    public void setTextureRect(String var1, float var2, float var3, float var4, float var5);

    public int getFaceCount();

    public void removeTexture(String var1);

    public void setColor(int var1, int var2, int var3, String var4);

    public void setColor(int var1, int var2, int var3);

    public WTVector3D getVertex(int var1, String var2);

    public WTVector3D getVertex(int var1);

    public void removeTexture();

    public void setPatchTileColor(int var1, int var2, byte var3, byte var4, byte var5, byte var6, String var7);

    public void setPatchTileColor(int var1, int var2, byte var3, byte var4, byte var5, byte var6);

    public void setPatchTileColor(int var1, int var2, byte var3, byte var4, byte var5);

    public void setPatchTileColor(int var1, int var2, int var3, int var4, int var5, int var6, String var7);

    public void setPatchTileColor(int var1, int var2, int var3, int var4, int var5, int var6);

    public void setVertexColor(int var1, byte var2, byte var3, byte var4, byte var5);

    public void setVertexColor(int var1, byte var2, byte var3, byte var4);

    public void setVertexColor(int var1, int var2, int var3, int var4, int var5);

    public void setVertexColor(int var1, int var2, int var3, int var4);

    public void setPatchTileUV(int var1, int var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, String var11);

    public void setPatchTileUV(int var1, int var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10);

    public void setVertexNormal(int var1, float var2, float var3, float var4);

    public int hasDxAnimations();

    public int removeVertices(int[] var1);

    public void clear(boolean var1);

    public void clear();

    public void setMaterial(int var1, int var2, int var3, float var4, int var5, int var6, int var7);

    public void setPatchTileMaterial(int var1, int var2, int var3, int var4, int var5, float var6, int var7, int var8, int var9, String var10);

    public void setPatchTileMaterial(int var1, int var2, int var3, int var4, int var5, float var6, int var7, int var8, int var9);

    public void setFace(int var1, int var2, int var3, int var4);

    public void setPatchHeightExtents(float var1, float var2);

    public void setDxAnimationRate(int var1, int var2);

    public void setDxAnimationRate(int var1);

    public int getDxAnimationRate(int var1);

    public int getDxAnimationRate();

    public void stopDxAnimation(int var1);

    public void stopDxAnimation();

    public void setRGBA(int var1, int var2, int var3, int var4, String var5);

    public void setRGBA(int var1, int var2, int var3, int var4);

    public void updateNormals(int var1);

    public void updateNormals();

    public void setPatchPtColor(int var1, int var2, byte var3, byte var4, byte var5, byte var6, String var7);

    public void setPatchPtColor(int var1, int var2, byte var3, byte var4, byte var5, byte var6);

    public void setPatchPtColor(int var1, int var2, byte var3, byte var4, byte var5);

    public void setPatchPtColor(int var1, int var2, int var3, int var4, int var5, int var6, String var7);

    public void setPatchPtColor(int var1, int var2, int var3, int var4, int var5, int var6);

    public void setFaceColor(int var1, byte var2, byte var3, byte var4, byte var5);

    public void setFaceColor(int var1, byte var2, byte var3, byte var4);

    public void setFaceColor(int var1, int var2, int var3, int var4, int var5);

    public void setFaceColor(int var1, int var2, int var3, int var4);

    public void setFaces(int[] var1, int[] var2, int var3, int var4, int var5);

    public void setFaces(int[] var1, int[] var2, int var3, int var4);

    public void setFaces(int[] var1, int[] var2, int var3);

    public void setFaces(int[] var1, int[] var2);

    public int addVertices(float[] var1, float[] var2, int var3, int var4, int var5);

    public int addVertices(float[] var1, float[] var2, int var3, int var4);

    public float getDxAnimationLength(int var1);

    public float getDxAnimationLength();

    public int addVertices(float[] var1, float[] var2, int var3);

    public int addVertices(float[] var1, float[] var2);

    public int addVertices(float[] var1);

    public void setPatchPtUV(int var1, int var2, float var3, float var4, String var5);

    public void setPatchPtUV(int var1, int var2, float var3, float var4);

    public void setScale(float var1, float var2, float var3);

    public void setScale(float var1);

    public void setVertexUV(int var1, float var2, float var3);

    public void setSurfaceShader(WTSurfaceShader var1, String var2, int var3);

    public void setSurfaceShader(WTSurfaceShader var1, String var2);

    public void setSurfaceShader(WTSurfaceShader var1);

    public void playDxAnimation(float var1, float var2, boolean var3, boolean var4, int var5);

    public void playDxAnimation(float var1, float var2, boolean var3, boolean var4);

    public void playDxAnimation(float var1, float var2, boolean var3);

    public void playDxAnimation(float var1, float var2);

    public void playDxAnimation(float var1);

    public void playDxAnimation();

    public void setPatchTileSurfaceShader(int var1, int var2, WTSurfaceShader var3, String var4);

    public void setPatchTileSurfaceShader(int var1, int var2, WTSurfaceShader var3);

    public void setVertexPosition(int var1, float var2, float var3, float var4);

    public void setPatchHeightWithString(String var1, int var2, int var3, int var4, int var5);

    public void setPatchHeightWithString(String var1, int var2, int var3, int var4);

    public void setPatchHeightWithString(String var1, int var2, int var3);

    public void setPatchHeightWithString(String var1, int var2);

    public void setPatchHeightWithString(String var1);

    public int addFaces(int[] var1, int var2, int var3);

    public int addFace(int var1, int var2, int var3);

    public int addFaces(int[] var1, int var2);

    public int addFaces(int[] var1);

    public void setVerticesPositions(int[] var1, float[] var2, int var3, int var4, int var5);

    public void setVerticesPositions(int[] var1, float[] var2, int var3, int var4);

    public void setVerticesPositions(int[] var1, float[] var2, int var3);

    public void setVerticesPositions(int[] var1, float[] var2);

    public void setAbsoluteScale(float var1, float var2, float var3);

    public void setAbsoluteScale(float var1);

    public void setFaceSurfaceShader(int var1, WTSurfaceShader var2);

    public void removePatchAreaTexture(int var1, int var2, int var3, int var4, String var5);

    public void removePatchAreaTexture(int var1, int var2, int var3, int var4);

    public void setFaceTexture(int var1, WTBitmap var2);

    public void setOpacity(int var1, String var2);

    public void setOpacity(int var1);

    public void setPatchPtPos(int var1, int var2, float var3, float var4, float var5, int var6);

    public void setPatchPtPos(int var1, int var2, float var3, float var4, float var5);

    public boolean isDxAnimationPlaying(int var1);

    public boolean isDxAnimationPlaying();

    public int removeVertex(int var1);

    public void setUVMapping(int var1);
}

