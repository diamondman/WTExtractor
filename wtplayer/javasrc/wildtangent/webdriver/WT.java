package wildtangent.webdriver;

//import wildtangent.webdriver.WTActor;
//import wildtangent.webdriver.WTAudioClip;
//import wildtangent.webdriver.WTAudioClip3D;
//import wildtangent.webdriver.WTBitmap;
//import wildtangent.webdriver.WTCamera;
//import wildtangent.webdriver.WTContainer;
//import wildtangent.webdriver.WTEvent;
//import wildtangent.webdriver.WTEventCallback;
//import wildtangent.webdriver.WTFile;
//import wildtangent.webdriver.WTFont;
//import wildtangent.webdriver.WTGroup;
//import wildtangent.webdriver.WTJoystick;
//import wildtangent.webdriver.WTKeyboardPollInfo;
//import wildtangent.webdriver.WTLight;
//import wildtangent.webdriver.WTModel;
//import wildtangent.webdriver.WTMousePollInfo;
//import wildtangent.webdriver.WTPortal;
//import wildtangent.webdriver.WTShadow;
//import wildtangent.webdriver.WTSpout;
//import wildtangent.webdriver.WTStage;
//import wildtangent.webdriver.WTString3D;
//import wildtangent.webdriver.WTSurfaceShader;
//import wildtangent.webdriver.WTSysInfo;
//import wildtangent.webdriver.WTVisualizer;

import wildtangent.webdriver.WTObject;

public interface WT {

    int extraThing();

    WTObject getSampleObject();

    //public WTGroup createGroupFromFile(String var1, int var2);
    //
    //public WTGroup createGroupFromFile(String var1);
    //
    //public WTKeyboardPollInfo pollKeyboard();
    //
    //public WTGroup createGroupFromFile(String var1, int var2, int var3, int var4);
    //
    //public String getVersion();
    //
    //public void debugWindow(boolean var1);
    //
    //public void setOnKeyboardEvent(WTEventCallback var1);
    //
    //public WTSysInfo getPerformanceInfo();
    //
    //public boolean getInitStatus(int var1);
    //
    //public int getDownloadInfo(int var1, int var2);
    //
    //public int getDownloadInfo(int var1);
    //
    //public void resetDownloadInfo();
    //
    //public WTSpout createSpout();
    //
    //public void setErrorHandling(int var1);
    //
    //public int getErrorHandling();
    //
    //public void outDebugString(String var1);
    //
    //public WTGroup createGroup();
    //
    //public WTStage createStage();
    //
    //public int getHeight();
    //
    //public WTSurfaceShader createSurfaceShader();
    //
    //public void setMousePosition(int var1, int var2);
    //
    //public void restoreResolution();
    //
    //public void stop();
    //
    //public void exec();
    //
    //public void sleep(int var1);
    //
    //public WTModel createPatch(int var1, int var2, float var3, float var4, float var5, float var6, boolean var7);
    //
    //public WTModel createPatch(int var1, int var2, float var3, float var4, float var5, float var6);
    //
    //public WTModel createPlane(float var1, float var2, boolean var3, float var4, float var5, int var6);
    //
    //public WTModel createPlane(float var1, float var2, boolean var3, float var4, float var5);
    //
    //public WTBitmap createBlankBitmap(int var1, int var2);
    //
    //public WTModel createPlane(float var1, float var2, boolean var3, float var4);
    //
    //public WTModel createPlane(float var1, float var2, boolean var3);
    //
    //public WTModel createPlane(float var1, float var2);
    //
    //public void freeDev();
    //
    //public void start();
    //
    //public WTAudioClip createAudioClip(String var1, int var2);
    //
    //public WTAudioClip createAudioClip(String var1);
    //
    //public WTFont createFont(int var1);
    //
    //public int getMaxFramesPerSecond();
    //
    //public WTModel createBox(float var1, float var2, float var3, int var4);
    //
    //public WTModel createBox(float var1, float var2, float var3);
    //
    //public void setMaxFramesPerSecond(int var1);
    //
    //public WTFont createFont();
    //
    //public WTPortal createPortal(float var1, float var2, WTCamera var3, int var4, boolean var5, boolean var6);
    //
    //public void setClipRect(int var1, int var2, int var3, int var4);
    //
    //public WTShadow createShadow(int var1, int var2, int var3);
    //
    //public WTShadow createShadow(int var1, int var2);
    //
    //public WTShadow createShadow(int var1);
    //
    //public WTShadow createShadow();
    //
    //public WTModel createModel(String var1, int var2);
    //
    //public WTModel createModel(String var1);
    //
    //public void setNotifyExceptionEvent(boolean var1);
    //
    //public boolean getNotifyExceptionEvent();
    //
    //public double getInfo(int var1, int var2);
    //
    //public double getInfo(int var1);
    //
    //public WTVisualizer createAudioVisualizer(String var1, String var2, int var3, int var4);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5, int var6, int var7, int var8);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5, int var6, int var7);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5, int var6);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3);
    //
    //public WTModel createMesh(float[] var1, int[] var2);
    //
    //public WTModel createMesh(float[] var1);
    //
    //public WTModel createMesh();
    //
    //public WTBitmap createBitmap(String var1, int var2);
    //
    //public WTBitmap createBitmap(String var1);
    //
    //public void setMouseCursorState(int var1);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5, int var6, int var7, int var8, int var9, int var10, int var11, int var12);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5, int var6, int var7, int var8, int var9, int var10, int var11);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5, int var6, int var7, int var8, int var9, int var10);
    //
    //public WTModel createMesh(float[] var1, int[] var2, float[] var3, float[] var4, byte[] var5, int var6, int var7, int var8, int var9);
    //
    //public WTString3D createString3D();
    //
    //public void focus();
    //
    //public boolean setResolution(int var1, int var2, int var3);
    //
    //public boolean setResolution(int var1, int var2);
    //
    //public Object getOption(int var1);
    //
    //public void setOption(int var1, Object var2);
    //
    //public void setOption(int var1, boolean var2);
    //
    //public void setOption(int var1, double var2);
    //
    //public void setOption(int var1, float var2);
    //
    //public void setOption(int var1, int var2);
    //
    //public int requestMouseControl();
    //
    //public WTLight createLight(int var1);
    //
    //public WTModel createLine(float var1, float var2, float var3, float var4, float var5, float var6, float var7, int var8, int var9, int var10);
    //
    //public WTFile readFile(String var1, int var2, int var3);
    //
    //public WTFile readFile(String var1, int var2);
    //
    //public WTContainer createContainer();
    //
    //public WTFile readFile(String var1);
    //
    //public int getMasterVolume();
    //
    //public void setMasterVolume(int var1);
    //
    //public void setRenderOption(int var1, int var2);
    //
    //public int getRenderOption(int var1);
    //
    //public void setMaxDownloads(int var1);
    //
    //public int getMaxDownloads();
    //
    //public WTEvent getEvent();
    //
    //public void setNotifyKeyboardEvent(boolean var1);
    //
    //public boolean getNotifyKeyboardEvent();
    //
    //public void setOnRenderEvent(WTEventCallback var1);
    //
    //public void setOnMouseEvent(WTEventCallback var1);
    //
    //public int checkVersion(String var1, String var2);
    //
    //public int checkVersion(String var1);
    //
    //public void setClientRect(int var1, int var2, int var3, int var4);
    //
    //public int designedForVersion(String var1, String var2, int var3);
    //
    //public int designedForVersion(String var1, String var2);
    //
    //public int designedForVersion(String var1);
    //
    //public WTMousePollInfo pollMouse();
    //
    //public WTJoystick createJoystick();
    //
    //public WTModel createCone(float var1, float var2, int var3, int var4);
    //
    //public WTEvent getRenderEvent();
    //
    //public void setNotifyRenderEvent(boolean var1);
    //
    //public boolean getNotifyRenderEvent();
    //
    //public void setNotifyMouseEvent(int var1);
    //
    //public int getNotifyMouseEvent();
    //
    //public void overrideExceptionEvent(int var1, boolean var2);
    //
    //public WTModel createSphere(float var1, int var2);
    //
    //public WTModel createSphere(float var1);
    //
    //public void setOptionString(String var1, String var2, String var3, int var4);
    //
    //public void setOptionString(String var1, String var2, String var3);
    //
    //public void setOnExceptionEvent(WTEventCallback var1);
    //
    //public String getRegistryStringValue(String var1, String var2);
    //
    //public String getFilesPath();
    //
    //public int getWidth();
    //
    //public boolean getIsUsable();
    //
    //public void shutdown();
    //
    //public WTModel createCylinder(float var1, float var2, int var3, int var4);
    //
    //public WTModel createBlankMesh();
    //
    //public void setLeftHanded(boolean var1);
    //
    //public int getRenderMode();
    //
    //public void setRenderMode(int var1);
    //
    //public void setHWND(int var1);
    //
    //public void NSActivate(int var1);
    //
    //public WTAudioClip3D createAudioClip3D(String var1, int var2);
    //
    //public WTAudioClip3D createAudioClip3D(String var1);
    //
    //public WTActor createActor(String var1, int var2);
    //
    //public WTActor createActor(String var1);
    //
    //public void setUseHAL(boolean var1);
    //
    //public WTGroup createGroupFromFile(String var1, int var2, int var3);
}
