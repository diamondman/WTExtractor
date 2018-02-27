package wildtangent.webdriver.impl;

public class WTSurfaceShader extends wildtangent.webdriver.jni.WTSurfaceShader
    implements wildtangent.webdriver.WTSurfaceShader {

    public WTSurfaceShader(long cPtr, boolean cMemoryOwn) {
        super(cPtr, cMemoryOwn);
    }


    public void setGeometryAmbientColor(int n, int n2, int n3) {
        this.setGeometryAmbientColor((byte)n, (byte)n2, (byte)n3);
    }

    public void setGeometrySpecularColor(int n, int n2, int n3) {
        this.setGeometrySpecularColor((byte)n, (byte)n2, (byte)n3);
    }

    public void setGeometryDiffuseColor(int n, int n2, int n3, int n4) {
        this.setGeometryDiffuseColor((byte)n, (byte)n2, (byte)n3, (byte)n4);
    }

    public void setGeometryEmissiveColor(int n, int n2, int n3) {
        this.setGeometryEmissiveColor((byte)n, (byte)n2, (byte)n3);
    }


    public void setOption(int n, Object object) {
        //this.internal_setOption(n, object);
        //this.setOption_xfer(n, object);
    }

    public void setOption(int n, boolean bl) {
        this.setOption(n, new Boolean(bl));
    }

    public void setOption(int n, double d) {
        this.setOption(n, new Double(d));
    }

    public void setOption(int n, float f) {
        this.setOption(n, new Float(f));
    }

    public void setOption(int n, int n2) {
        this.setOption(n, new Integer(n2));
    }

    public void setOnLoad(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTSurfaceShader.setOnLoad(WTOnLoadEvent)}");
        callback.onLoadComplete(this);
        this.setOnLoad(new InternalLoadEvent(callback));
    };

    public void setOnLoadedWithChildren(wildtangent.webdriver.WTOnLoadEvent callback){
        System.out.println("calling JAVA WTAPI {void WTSurfaceShader.setOnLoadedWithChildren(WTOnLoadEvent)}");
        callback.onLoadComplete(this);
        this.setOnLoadedWithChildren(new InternalLoadEvent(callback));
    };

}

