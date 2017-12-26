package wildtangent.webdriver.impl;

//import wildtangent.webdriver.WTActor;
//import wildtangent.webdriver.WTGroup;

public abstract class WT extends wildtangent.webdriver.jni.WT
    implements wildtangent.webdriver.WT {

    public int extraThing(){
        return 0;
    }

    //public WTActor createActor(String string) {
    //    return this.createActor(string, 0);
    //}
    //
    //public WTAudioClip createAudioClip(String string) {
    //    return this.createAudioClip(string, 0);
    //}
    //
    //public WTAudioClip3D createAudioClip3D(String string) {
    //    return this.createAudioClip3D(string, 0);
    //}
    //
    //public WTBitmap createBitmap(String string) {
    //    return this.createBitmap(string, 0);
    //}
    //
    //public WTModel createBox(float f, float f2, float f3) {
    //    return this.createBox(f, f2, f3, 3);
    //}
    //
    //public WTFont createFont() {
    //    return this.createFont(0);
    //}
    //
    //public WTGroup createGroupFromFile(String string, int n) {
    //    return this.createGroupFromFile(string, n, 0, 0);
    //}
    //
    //public WTGroup createGroupFromFile(String string) {
    //    return this.createGroupFromFile(string, 0, 0, 0);
    //}
    //
    //public WTGroup createGroupFromFile(String string, int n, int n2) {
    //    return this.createGroupFromFile(string, n, n2, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3, byte[] arrby, int n, int n2, int n3) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, arrby, n, n2, n3, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3, byte[] arrby, int n, int n2) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, arrby, n, n2, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3, byte[] arrby, int n) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, arrby, n, -1, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3, byte[] arrby) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, arrby, -1, -1, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, null, -1, -1, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2) {
    //    return this.createMesh(arrf, arrn, arrf2, null, null, -1, -1, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn) {
    //    return this.createMesh(arrf, arrn, null, null, null, -1, -1, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf) {
    //    return this.createMesh(arrf, null, null, null, null, -1, -1, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh() {
    //    return this.createMesh(null, null, null, null, null, -1, -1, 0, 0, 0, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3, byte[] arrby, int n, int n2, int n3, int n4, int n5, int n6) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, arrby, n, n2, n3, n4, n5, n6, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3, byte[] arrby, int n, int n2, int n3, int n4, int n5) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, arrby, n, n2, n3, n4, n5, 0, 0);
    //}
    //
    //public WTModel createMesh(float[] arrf, int[] arrn, float[] arrf2, float[] arrf3, byte[] arrby, int n, int n2, int n3, int n4) {
    //    return this.createMesh(arrf, arrn, arrf2, arrf3, arrby, n, n2, n3, n4, 0, 0, 0);
    //}
    //
    //public WTModel createModel(String string) {
    //    return this.createModel(string, 0);
    //}
    //
    //public WTModel createPatch(int n, int n2, float f, float f2, float f3, float f4) {
    //    return this.createPatch(n, n2, f, f2, f3, f4, false);
    //}
    //
    //public WTModel createPlane(float f, float f2, boolean bl, float f3, float f4) {
    //    return this.createPlane(f, f2, bl, f3, f4, 0);
    //}
    //
    //public WTModel createPlane(float f, float f2, boolean bl, float f3) {
    //    return this.createPlane(f, f2, bl, f3, 0.0f, 0);
    //}
    //
    //public WTModel createPlane(float f, float f2, boolean bl) {
    //    return this.createPlane(f, f2, bl, 0.0f, 0.0f, 0);
    //}
    //
    //public WTModel createPlane(float f, float f2) {
    //    return this.createPlane(f, f2, false, 0.0f, 0.0f, 0);
    //}
    //
    //public WTModel createSphere(float f) {
    //    return this.createSphere(f, 8);
    //}
    //
    //public WTShadow createShadow(int n, int n2) {
    //    return this.createShadow(n, n2, 128);
    //}
    //
    //public WTShadow createShadow(int n) {
    //    return this.createShadow(n, 128, 128);
    //}
    //
    //public WTShadow createShadow() {
    //    return this.createShadow(0, 128, 128);
    //}
    //
    //
    //
    //
    //public int getDownloadInfo(int n) {
    //    return this.getDownloadInfo(n, 0);
    //}
    //
    //public double getInfo(int n) {
    //    return this.getInfo(n, 0);
    //}
    //
    //
    //
    //
    //public void setOptionString(String string, String string2, String string3) {
    //    this.setOptionString(string, string2, string3, 0);
    //}
    //
    //public void setOption(int n, Object object) {
    //    //this.setOption_xfer(n, object);
    //}
    //
    //public void setOption(int n, boolean bl) {
    //    this.setOption(n, new Boolean(bl));
    //}
    //
    //public void setOption(int n, double d) {
    //    this.setOption(n, new Double(d));
    //}
    //
    //public void setOption(int n, float f) {
    //    this.setOption(n, new Float(f));
    //}
    //
    //public void setOption(int n, int n2) {
    //    this.setOption(n, new Integer(n2));
    //}
    //
    //public boolean setResolution(int n, int n2) {
    //    return this.setResolution(n, n2, 0);
    //}
    //
    //
    //
    //
    //
    //public int checkVersion(String string) {
    //    return this.checkVersion(string, null);
    //}
    //
    //public int designedForVersion(String string, String string2, int n) {
    //    this.internal_designedForVersion(string, string2, n);
    //    return this.designedForVersion_xfer(string, string2, n);
    //}
    //
    //public int designedForVersion(String string, String string2) {
    //    return this.designedForVersion(string, string2, 1);
    //}
    //
    //public int designedForVersion(String string) {
    //    return this.designedForVersion(string, "FULL", 1);
    //}
    //
    //public void focus() {
    //    //this.takeFocus();
    //}
    //
    //public WTFile readFile(String string, int n) {
    //    return this.readFile(string, n, 2);
    //}
    //
    //public WTFile readFile(String string) {
    //    return this.readFile(string, 0, 2);
    //}
    //
    //public synchronized void shutdown() {
    //    this.userobjects.clear();
    //    if (this.iWT != null) {
    //        RNIFactory.Remove(this);
    //        this.RNI_shutdown(this.com_int);
    //    }
    //    this.rni_wt = null;
    //    this.iWT = null;
    //}
    //
    //public void sleep(int n) {
    //    try {
    //        Thread.currentThread();
    //        Thread.sleep(n > 1000 ? 1000 : n);
    //        return;
    //    }
    //    catch (Exception exception) {
    //        return;
    //    }
    //}

}
